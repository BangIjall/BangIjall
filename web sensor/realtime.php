<?php 
require './assets/inc/function.php';
$row1 = mysqli_fetch_assoc($result1);

?>
<div class="container-fluid">
    <h4 class="page-title">Dashboard</h4>
    <div class="row">
        <div class="col-md-4">
            <div class="card card-stats card-warning">
                <div class="card-body ">
                    <div class="row">
                        <div class="col-5">
                            <div class="icon-big text-center">
                                <i class="la la-sun-o"></i>
                            </div>
                        </div>
                        <div class="col-7 d-flex align-items-center">
                            <div class="numbers">
                                <p class="card-category">Cahaya</p>
                                <h4 class="card-title"><?= $row1["cahaya"]; ?></h4>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="col-md-4">
            <div class="card card-stats card-success">
                <div class="card-body ">
                    <div class="row">
                        <div class="col-5">
                            <div class="icon-big text-center">
                                <i class="las la-temperature-high"></i>
                            </div>
                        </div>
                        <div class="col-7 d-flex align-items-center">
                            <div class="numbers">
                                <p class="card-category">Temperature</p>
                                <h4 class="card-title"><?= $row1["temperatur"]; ?></h4>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
        <div class="col-md-4">
            <div class="card card-stats card-primary">
                <div class="card-body">
                    <div class="row">
                        <div class="col-5">
                            <div class="icon-big text-center">
                                <i class="las la-water"></i>
                            </div>
                        </div>
                        <div class="col-7 d-flex align-items-center">
                            <div class="numbers">
                                <p class="card-category">Kelembaban</p>
                                <h4 class="card-title"><?= $row1["kelembapan"]; ?></h4>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>