<?php
require "fpdf.php";
$conn = mysqli_connect("localhost", "siagabanjir", "WebsiteAndroid2022", "u665944158_siagabanjir");
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
}

$tipe = $_GET['tipe'];
$tglawal = $_GET['tglawal'];
$tglmod = date('Y:m:d', strtotime($tglawal . '+1 day'));
$tglakhir = $_GET['tglakhir'];

class myPDF extends FPDF
{
    function header()
    {
        $tglawal = $_GET['tglawal'];
        $tglakhir = $_GET['tglakhir'];
        $title = $_GET['title'];
        $this->Image('SB.png', 10, 6, 20, 20);
        $this->SetFont('Times', 'B', 14);
        $this->Cell(190, 6, 'Data Parameter' . ' ' . $title, 0, 0, 'C');
        $this->Ln();
        $this->SetFont('Times', '', 12);
        if ($tglawal !== '' and $tglakhir !== '') {
            $this->Cell(190, 10, $tglawal . ' - ' . $tglakhir, 0, 0, 'C');
        } else {
            $this->Cell(190, 10, $tglawal, 0, 0, 'C');
        }
        $this->Ln(20);
    }
    function footer()
    {
        $this->SetY(-15);
        $this->SetFont('Times', '', 8);
        $this->SetLeftMargin(-100);
        $this->Cell(130, 10, 'Page ' . $this->PageNo . '/{nb}', 0, 0, 'C');
    }
    function headerTable()
    {
        $tipe = $_GET['tipe'];
        $this->SetFont('Times', 'B', 12);
        $this->SetLeftMargin(30);
        $this->Cell(60, 10, 'Waktu', 1, 0, 'C');
        if ($tipe == 'curah') {
            $this->Cell(40, 10, 'Nilai(mm)', 1, 0, 'C');
        } elseif ($tipe == 'level') {
            $this->Cell(40, 10, 'Nilai(cm)', 1, 0, 'C');
        } elseif ($tipe == 'laju') {
            $this->Cell(40, 10, 'Nilai(m/s)', 1, 0, 'C');
        }

        $this->Cell(50, 10, 'Status', 1, 0, 'C');
        $this->Ln();
    }
    function populateTable($conn)
    {
        $tipe = $_GET['tipe'];
        $tglawal = $_GET['tglawal'];
        $tglmod = date('Y:m:d', strtotime($tglawal . '+1 day'));
        $tglakhir = $_GET['tglakhir'];
        $this->SetFont('Times', '', 12);
        $this->SetLeftMargin(30);
        if ($tglawal == $tglakhir) {
            $query = mysqli_query($conn, "SELECT value1,value2,reading_time FROM $tipe WHERE reading_time >='$tglawal' and reading_time <='$tglmod'");
        } else {
            $query = mysqli_query($conn, "SELECT value1,value2,reading_time FROM $tipe WHERE reading_time >='$tglawal' and reading_time <='$tglakhir'");
        }
        while ($data = mysqli_fetch_array($query)) {
            $this->Cell(60, 10, $data['reading_time'], 1, 0, 'C');
            $this->Cell(40, 10, $data['value1'], 1, 0, 'C');
            $this->Cell(50, 10, $data['value2'], 1, 0, 'C');
            $this->Ln();
        }
    }
}

$pdf = new myPDF();
$pdf->AliasNbPages();
$pdf->AddPage('P', 'A4', 0);
$pdf->headerTable();
$pdf->populateTable($conn);
$pdf->Output();
