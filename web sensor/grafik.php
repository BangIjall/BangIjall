<?php
require './assets/inc/function.php';
?>
<div class="container-fluid">
    <h4 class="page-title">Grafik</h4>
    <div class="row">
        <div class="col-sm-8">
            <div class="card">
                <div class="card-header">
                    <p class="card-category">
                        Grafik Data Sensor</p>
                </div>
                <div class="card-body">
                    <canvas id="myChart1"></canvas>
                </div>
            </div>
        </div>
    </div>
</div>
<script>
    // setup 
    var data = {
        labels: [
            <?php
            foreach ($result as $row) {
            ?> '<?php echo $row["waktu"]  ?>',
            <?php } ?>
        ],
        datasets: [{
                label: 'Temperatur',
                data: [
                    <?php
                    foreach ($result as $row) {
                    ?> '<?php echo $row["temperatur"]  ?>',
                    <?php } ?>
                ],
                fill: true,
                backgroundColor: "rgba(255,228,225,0.5)"
            }, {
                label: 'Kelembaban',
                data: [
                    <?php
                    foreach ($result as $row) {
                    ?> '<?php echo $row["kelembapan"]  ?>',
                    <?php } ?>
                ],
                fill: true,
                backgroundColor: "rgba(219,112,147,0.8)"
            },
            {
                label: 'Cahaya',
                data: [
                    <?php
                    foreach ($result as $row) {
                    ?> '<?php echo $row["cahaya"]  ?>',
                    <?php } ?>
                ],
                fill: true,
                backgroundColor: "rgba(255,20,147,1)"
            }
        ]
    };

    // config 
    var config = {
        type: 'line',
        data,
        options: {
            scales: {
                y: {
                    beginAtZero: true
                }
            }
        }
    };

    // render init block
    var myChart = new Chart(
        document.getElementById('myChart1'),
        config
    );
</script>