<?php
// $conn = mysqli_connect("localhost","u665944158_siagabanjir","WebsiteAndroid2022","u665944158_siagabanjir");
$conn = mysqli_connect("localhost", "siagabanjir", "WebsiteAndroid2022", "u665944158_siagabanjir");
if (isset($_GET["p"])) {
    $p = $_GET["p"];
    if ($p == 'realtime') {
        $allcurah = mysqli_query($conn, "SELECT value1, value2,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from curah order by id desc");
        $alllaju = mysqli_query($conn, "SELECT value1, value2,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from laju order by id desc");
        $alllevel = mysqli_query($conn, "SELECT value1, value2,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from level order by id desc");
        $rallcurah = mysqli_fetch_row($allcurah);
        $ralllaju = mysqli_fetch_row($alllaju);
        $ralllevel = mysqli_fetch_row($alllevel);
        // $nilaicurah = $rallcurah[0];
        // $statuscurah = $rallcurah[1];
        $waktucurah = $rallcurah[2];
        // $nilailaju = $ralllaju[0];
        // $statuslaju = $ralllaju[1];
        $waktulaju = $ralllaju[2];
        // $nilailevel = $ralllevel[0];
        // $statuslevel = $ralllevel[1];
        $waktulevel = $ralllevel[2];
        $data = array('waktucurah' => $waktucurah, 'waktulaju' => $waktulaju, 'waktulevel' => $waktulevel);
        echo json_encode($data);
    } else if ($p == 'tabel') {
        $q = $_GET['q'];
        if ($q == 'level') {
            $param = mysqli_query($conn, "SELECT value1,value2,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from $q");
        } elseif ($q == 'laju') {
            $param = mysqli_query($conn, "SELECT WaterFlow1,WaterFlow2,WaterFlow3,WaterFlow4,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from $q");
        } elseif ($q == 'curah') {
            $param = mysqli_query($conn, "SELECT value1,Parameter_hujan as hujan,date_format(reading_time,'%d-%m-%Y %H:%i:%s') as waktu from $q");
        }
        $data = array();
        while ($row = mysqli_fetch_assoc($param)) {
            $data['data'][] = $row;
        }
        echo json_encode($data, JSON_PRETTY_PRINT);
    } else if ($p == 'grafik') {
        $q = $_GET['q'];
        $time = mysqli_query($conn, "SELECT date_format(reading_time, '%H:%i') as waktu FROM $q order by id asc limit 20");
        if ($q == 'laju') {
            $param1 = mysqli_query($conn, "SELECT WaterFlow1 FROM $q order by id asc");
            $param2 = mysqli_query($conn, "SELECT WaterFlow2 FROM $q order by id asc");
            $param3 = mysqli_query($conn, "SELECT WaterFlow3 FROM $q order by id asc");
            $param4 = mysqli_query($conn, "SELECT WaterFlow4 FROM $q order by id asc");
        }
        $param = mysqli_query($conn, "SELECT value1 FROM $q order by id asc");
        $rows = array();
        $rows['param'] = 'time';
        while ($t = mysqli_fetch_array($time)) {
            $rows['data'][] = $t['waktu'];
        }
        $rows1 = array();
        $rows1['param'] = $q;
        while ($qq = mysqli_fetch_array($param)) {
            $rows1['data'][] = $qq['value1'];
        }
        $gg = array();
        array_push($gg, $rows);
        array_push($gg, $rows1);
        echo json_encode($gg, JSON_NUMERIC_CHECK);
    } else if ($p == 'grafikk') {
        $q = $_GET['q'];
        $time = mysqli_query($conn, "SELECT date_format(reading_time, '%H:%i') as waktu FROM $q order by id asc limit 20");
        if ($q == 'laju') {
            $param1 = mysqli_query($conn, "SELECT WaterFlow1 FROM $q order by id asc");
            $param2 = mysqli_query($conn, "SELECT WaterFlow2 FROM $q order by id asc");
            $param3 = mysqli_query($conn, "SELECT WaterFlow3 FROM $q order by id asc");
            $param4 = mysqli_query($conn, "SELECT WaterFlow4 FROM $q order by id asc");
        }
        $param = mysqli_query($conn, "SELECT value1 FROM $q order by id asc");
        $rows = array();
        $rows['param'] = 'time';
        while ($t = mysqli_fetch_array($time)) {
            $rows['data'][] = $t['waktu'];
        }

        if ($q == 'laju') {
            $rowsw1 = array();
            $rowsw1['param'] = 'Waterflow1';
            while ($w1 = mysqli_fetch_array($param1)) {
                $rowsw1['data'][] = $w1['WaterFlow1'];
            }

            $rowsw2 = array();
            $rowsw2['param'] = 'Waterflow2';
            while ($w2 = mysqli_fetch_array($param2)) {
                $rowsw2['data'][] = $w2['WaterFlow2'];
            }

            $rowsw3 = array();
            $rowsw3['param'] = 'Waterflow3';
            while ($w3 = mysqli_fetch_array($param3)) {
                $rowsw3['data'][] = $w3['WaterFlow3'];
            }

            $rowsw4 = array();
            $rowsw4['param'] = 'Waterflow4';
            while ($w4 = mysqli_fetch_array($param4)) {
                $rowsw4['data'][] = $w4['WaterFlow4'];
            }
        }

        if ($q == 'curah' || $q == 'level') {
            $rows1 = array();
            $rows1['param'] = $q;
            while ($qq = mysqli_fetch_array($param)) {
                $rows1['data'][] = $qq['value1'];
            }
        }


        $gg = array();
        array_push($gg, $rows);
        if ($q == 'laju') {
            array_push($gg, $rowsw1);
            array_push($gg, $rowsw2);
            array_push($gg, $rowsw3);
            array_push($gg, $rowsw4);
        }

        array_push($gg, $rows1);

        echo json_encode($gg, JSON_NUMERIC_CHECK);
    }
} else {
    echo 'p not defined';
}
