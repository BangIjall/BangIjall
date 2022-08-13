<?php
require './assets/inc/function.php';
?>
<div class="container-fluid">
    <h4 class="page-title">Tabel</h4>
    <div class="row">
        <div class="col-md-12">
            <div class="card">
                <div class="card-header ">
                    <h4 class="card-title">Tabel Sensor</h4>
                </div>
                <div class="card-body">
                    <table class="table table-head-bg-success table-striped table-hover text-center">
                        <thead>
                            <tr>
                                <th scope="col">Waktu</th>
                                <th scope="col">Sensor Cahaya (lx)</th>
                                <th scope="col">Sensor Temperatur (°C)</th>
                                <th scope="col">Sensor Kelembapan Udara (%)</th>
                            </tr>
                        </thead>
                        <tbody>
                            <?php while ($row = mysqli_fetch_assoc($result)) : ?>
                                <tr>
                                    <td><?= $row["waktu"]; ?></td>
                                    <td><?= $row["cahaya"]; ?></td>
                                    <td><?= $row["temperatur"]; ?></td>
                                    <td><?= $row["kelembapan"]; ?></td>
                                </tr>
                            <?php endwhile; ?>
                        </tbody>
                    </table>
                </div>
            </div>
        </div>
    </div>
</div>