<?php 

      $conn = mysqli_connect("localhost","phpmyadmin", "password", "3sensor");

      $result = mysqli_query($conn, "SELECT * FROM sensortiga ORDER BY id DESC");

      $result1 = mysqli_query($conn, "SELECT * FROM sensortiga ORDER BY id DESC limit 1");

?>



<div class="container text-center" id= "judul2">Data Realtime</div>

<div class="row justify-content-center" style="margin-left:20px;">

    <?php $row1 = mysqli_fetch_assoc($result);?>

        <div class="col-3" id="cahaya"> 

            <div id="cahaya1">

                <h6>CAHAYA (Lx)</h6>

                <hr id="garischy" size="5px;">

                <img src="gambar/sun.png" alt="" width="40" height="40">

                <?= $row1["cahaya"]; ?>

            </div>

        </div>

        <div class="col-3" id="temperatur">

            <div id="temp1">

                <h6>TEMPERATUR (°C)</h6>

                <hr id="garischy" size="5px;">

                <img src="gambar/temp.png" alt="" width="50" height="50">

                <?= $row1["temperatur"]; ?>

            </div>

        </div>

        <div class="col-3" id="kelembapan">

            <div id="kelembapan1">

                <h6>KELEMBAPAN UDARA (%)</h6>

                <hr id="garischy" size="5px;">

                <img src="gambar/hum.png" alt="" width="50" height="50">

                <?= $row1["kelembapan"]; ?>

            </div>

        </div>

</div>



<div class="container text-center" id= "judul3">Grafik Sensor

    <script src="https://www.gstatic.com/charts/loader.js"></script>

    <div id="myChart" style="max-width:1500px; height:400px"></div>

    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>

        <script type="text/javascript">

        google.charts.load('current', {'packages':['corechart']});

        google.charts.setOnLoadCallback(drawChart);

        function drawChart() {

            var data = google.visualization.arrayToDataTable([

            ['waktu', 'cahaya'],

            //PHP Code 

            <?php

                $query="select * from sensortiga";

                $res=mysqli_query($conn,$query);

                while($data=mysqli_fetch_array($res)){

                    $waktu=$data['waktu'];

                    $cahaya=$data['cahaya'];

            ?>  

            ['<?php echo $waktu;?>',<?php echo $cahaya;?>], 

            <?php      

                }

            ?> 

            ]);

            

            var options = {

            title: 'Sensor Cahaya',

            curveType: 'function',

            hAxis: {title: 'Waktu'},

            vAxis: {title: 'Cahaya (Lx)'},

            colors:['red'],

            legend: 'none',

            chartArea: {

                backgroundColor: {

                     stroke: '#FFC0CB',

                     strokeWidth: 3

                }

            }

            };

            var chart = new google.visualization.AreaChart (document.getElementById('myChart'));

            chart.draw(data, options);

        }

    </script>

    <script src="https://www.gstatic.com/charts/loader.js"></script>

    <div id="myChart1" style="max-width:1500px; height:400px"></div>

    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>

        <script type="text/javascript">

        google.charts.load('current', {'packages':['line']});

        google.charts.setOnLoadCallback(drawChart);

        function drawChart() {

            var data = google.visualization.arrayToDataTable([

            ['waktu', 'temperatur'],

            //PHP Code 

            <?php

                $query="select * from sensortiga";

                $res=mysqli_query($conn,$query);

                while($data=mysqli_fetch_array($res)){

                    $waktu=$data['waktu'];

                    $temperatur=$data['temperatur'];

            ?>  

            ['<?php echo $waktu;?>',<?php echo $temperatur;?>], 

            <?php      

                }

            ?> 

            ]);

            var options = {

            title: 'Sensor Temperatur',

            curveType: 'function',

            hAxis: {title: 'Waktu'},

            vAxis: {title: 'Temperatur (°C)'},

            colors:['#e2b41e'],

            legend: 'none',

            chartArea: {

                backgroundColor: {

                     stroke: '#ffdc69',

                     strokeWidth: 3

                }

            }

            };

            var chart = new google.visualization.AreaChart (document.getElementById('myChart1'));

            chart.draw(data, options);

        }

    </script>

    <script src="https://www.gstatic.com/charts/loader.js"></script>

    <div id="myChart2" style="max-width:1500px; height:400px"></div>

    <script type="text/javascript" src="https://www.gstatic.com/charts/loader.js"></script>

        <script type="text/javascript">

        google.charts.load('current', {'packages':['line']});

        google.charts.setOnLoadCallback(drawChart);

        function drawChart() {

            var data = google.visualization.arrayToDataTable([

            ['waktu', 'kelembapan'],

            //PHP Code 

            <?php

                $query="select * from sensortiga";

                $res=mysqli_query($conn,$query);

                while($data=mysqli_fetch_array($res)){

                    $waktu=$data['waktu'];

                    $kelembapan=$data['kelembapan'];

            ?>  

            ['<?php echo $waktu;?>',<?php echo $kelembapan;?>], 

            <?php      

                }

            ?> 

            ]);

            var options = {

            title: 'Sensor Kelembapan Udara',

            curveType: 'function',

            hAxis: {title: 'Waktu'},

            vAxis: {title: 'Kelembapan Udara (%)'},

            colors:['#1ee297'],

            legend: 'none',

            chartArea: {

                backgroundColor: {

                     stroke: '#73ffc9',

                     strokeWidth: 3

                }

            }

            };

            var chart = new google.visualization.AreaChart (document.getElementById('myChart2'));

            chart.draw(data, options);

        }

    </script>

</div>



<div class="container text-center" id= "judul1">Tabel Sensor</div>    

<table class="table table-dark table-hover text-center mt-3" style="color:pink;">

        <thead>

            <tr>

            <th scope="col">Waktu</th>

            <th scope="col">Sensor Cahaya (lx)</th>

            <th scope="col">Sensor Temperatur (°C)</th>

            <th scope="col">Sensor Kelembapan Udara (%)</th>

            </tr>

        </thead>

        <tbody>

        <?php while($row = mysqli_fetch_assoc($result)) :?>

            <tr>

                <td><?= $row["waktu"]; ?></td>

                <td><?= $row["cahaya"]; ?></td>

                <td><?= $row["temperatur"]; ?></td>

                <td><?= $row["kelembapan"]; ?></td>

            </tr>

        <?php endwhile; ?>  

        </tbody>

    </table>

