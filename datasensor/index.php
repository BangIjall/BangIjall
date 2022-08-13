<!doctype html>

<html lang="en">

  <head>

    <!-- Required meta tags -->

    <meta charset="utf-8">

    <meta name="viewport" content="width=device-width, initial-scale=1">



    <!-- Bootstrap CSS -->

    <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-1BmE4kWBq78iYhFldvKuhfTAU6auU8tT94WrHftjDbrCEXSU1oBoqyl2QvZ6jIW3" crossorigin="anonymous">

    <link rel="stylesheet" href="style.css">

    <title>Data Sensor</title>

    <script>

      var refreshId = setInterval(function()

      {

      $('#on').load('isi.php');

      }, 5000);

    </script>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

    <script src="https://www.gstatic.com/charts/loader.js"></script>

    <script src="https://code.jquery.com/jquery-3.6.0.js" integrity="sha256-H+K7U5CnXl1h5ywQfKtSj8PCmoN9aaq30gDh27Xc0jk=" crossorigin="anonymous"></script>

  </head>

  <body>

  <nav class="navbar sticky-top navbar-expand-lg navbar-light navbar-fixed-top" style="background:pink;">

  <div class="container-fluid">

    <a class="navbar-brand">

        <img src="gambar/polines.png" alt="" width="30" height="30" class="d-inline-block align-text-top">

        Data Sensor

    </a>

    <button class="navbar-toggler" type="button" data-bs-toggle="collapse" data-bs-target="#navbarNavDropdown" aria-controls="navbarNavDropdown" aria-expanded="false" aria-label="Toggle navigation">

      <span class="navbar-toggler-icon"></span>

    </button>

    <div class="collapse navbar-collapse" id="navbarNavDropdown">

      <ul class="navbar-nav">

        <li class="nav-item mx-2">

          <a class="nav-link" aria-current="page" href="#judul2">Data Realtime</a>

        </li>

        <li class="nav-item dropdown mx-2">

          <a class="nav-link dropdown-toggle" href="#judul3" id="navbarDropdown" role="button" data-bs-toggle="dropdown" aria-expanded="false">

            Grafik Sensor

          </a>

          <ul class="dropdown-menu" aria-labelledby="navbarDropdown">

            <li><a class="dropdown-item" href="#myChart">Sensor Cahaya</a></li>

            <li><a class="dropdown-item" href="#myChart1">Sensor Temperatur</a></li>

            <li><a class="dropdown-item" href="#myChart2">Sensor Kelembapan Udara</a></li>

          </ul>

        </li>

        <li class="nav-item mx-2">

          <a class="nav-link" aria-current="page" href="#judul1">Tabel Sensor</a>

        </li>

      </ul>

    </div>

  </div>

</nav>

    <div class="container" id= "on"></div>

   

    <!-- Optional JavaScript; choose one of the two! -->



    <!-- Option 1: Bootstrap Bundle with Popper -->

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-ka7Sk0Gln4gmtz2MlQnikT1wXgYsOg+OMhuP+IlRH9sENBO0LRn5q+8nbTov4+1p" crossorigin="anonymous"></script>



    <!-- Option 2: Separate Popper and Bootstrap JS -->

    <!--

    <script src="https://cdn.jsdelivr.net/npm/@popperjs/core@2.10.2/dist/umd/popper.min.js" integrity="sha384-7+zCNj/IqJ95wo16oMtfsKbZ9ccEh31eOz1HGyDuCQ6wgnyJNSYdrPa03rtR1zdB" crossorigin="anonymous"></script>

    <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.1.3/dist/js/bootstrap.min.js" integrity="sha384-QJHtvGhmr9XOIpI6YVutG+2QOK9T+ZnN4kzFN1RtK3zEFEIsxhlmWl5/YESvpZ13" crossorigin="anonymous"></script>

    -->

  

      <footer class="footer">

        <p>Design by 

          Annisa Bunga Salsabila</p>

      </footer>

  </body>

</html>

