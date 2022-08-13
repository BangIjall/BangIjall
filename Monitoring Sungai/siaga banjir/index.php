<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="utf-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no" />
    <meta name="description" content="" />
    <meta name="author" content="" />
    <title>Sistem Monitoring - Home</title>
    <link href="vendor/fontawesome-free/css/all.min.css" rel="stylesheet" type="text/css" />
    <link href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i" rel="stylesheet" />
    <link href="css/sb-admin-2.min.css" rel="stylesheet" />
    <link rel="stylesheet" href="./css/highcharts.css">
</head>

<body id="page-top">
    <!-- Page Wrapper -->
    <div id="wrapper">
        <!-- Content Wrapper -->
        <div id="content-wrapper" class="d-flex flex-column">
            <!-- Main Content -->
            <div id="content">
                <nav class="navbar navbar-expand navbar-light bg-white topbar mb-4 static-top shadow">
                    <h3 class="mr-auto ml-md-3 ml-auto my-2 my-md-0 mw-100 text-gray-800 align-content-center">Siaga Banjir</h2>
                        <ul class="navbar-nav ml-auto">
                            <!-- Nav Item - User Information -->
                            <li class="nav-item dropdown no-arrow">
                                <a class="nav-link dropdown-toggle" href="#" id="userDropdown" style="cursor: default;" role="button" data-toggle="dropdown" aria-haspopup="true" aria-expanded="false">
                                    <span class="mr-2 d-none d-lg-inline text-gray-600 small">admin</span>
                                    <img class="img-profile rounded-circle" src="img/SB.png">
                                </a>
                            </li>
                        </ul>
                </nav>
                <!-- End of Topbar -->
                <!-- Begin Page Content -->
                <div class="container-fluid">
                    <!-- Content Row -->
                    <div class="row justify-content-center">
                        <div class="py-2 col-lg-12">
                            <div class="card shadow mb-4">
                                <div class="card-header py-3">
                                    <h4 class="m-0 font-weight-bold text-primary text-center">
                                        CURAH HUJAN
                                    </h4>
                                </div>
                                <div class="card-body">
                                    <div id="rcurah" class="row">
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="frcurah"></span>
                                                <span class="text-gray-600">mm</span>
                                            </h1>
                                        </div>
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="rstatuscurah"></span>
                                            </h1>
                                        </div>
                                    </div>
                                    <div id="gcurah" style="display: none;">
                                        <figure class="highcharts-figure">
                                            <div id="curahchart"></div>
                                        </figure>
                                        <div class="text-center mt-1">
                                            <button id="tutupgcurah" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="fpdfcurah" style="display: none;">
                                        <div class="row align-content-center justify-content-center text-center py-1">
                                            <div class="col-lg-12" style="max-width: 400px;">
                                                <form class="user" id="formcurah">
                                                    <input type="hidden" name="tipe" value="curah">
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl1" id="exampleInputEmail" aria-describedby="emailHelp">
                                                    </div>
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl2" id="exampleInputPassword">
                                                    </div>
                                                    <button id="expdfcurah" class="btn btn-primary btn-user btn-block" value="expdfcurah">
                                                        Export
                                                    </button>
                                                </form>
                                            </div>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutupfcurah" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="tcurah" style="display: none;">
                                        <div style="height: 167px;overflow: scroll;overflow-x: hidden;">
                                            <table class="table table-bordered" id="tabelcurah" width="100%" cellspacing="0">
                                                <thead>
                                                    <tr>
                                                        <th>Waktu</th>
                                                        <th>Nilai</th>
                                                        <th>Paramter Hujan</th>
                                                    </tr>
                                                </thead>
                                            </table>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutuptcurah" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                </div>
                                <div id="fcurah" class="card-footer py-3">
                                    <div class="row d-flex flex-row align-items-center">
                                        <div class="col-lg-6">
                                            <h6 class="m-0 font-weight-bold text-primary waktucurah">
                                            </h6>
                                        </div>
                                        <div class="col-lg-6 text-xl-right">
                                            <button id="bukagcurah" class=" btn btn-sm ml-auto btn-primary shadow-sm" value="curah">
                                                <i class="fas fa-chart-line fa-sm text-white-50"></i> Grafik
                                            </button>
                                            <button id="bukatcurah" class="btn btn-sm ml-auto btn-primary shadow-sm" value="curah">
                                                <i class="fas fa-table fa-sm text-white-50"></i> Tabel
                                            </button>
                                            <button id="bukafcurah" class="btn btn-sm ml-auto btn-primary shadow-sm" value="curah">
                                                <i class="fas fa-file-pdf fa-sm text-white-50"></i> PDF
                                            </button>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="py-2 col-lg-6">
                            <div class="card shadow mb-4">
                                <div class="card-header py-3">
                                    <h4 class="m-0 font-weight-bold text-primary text-center">
                                        LEVEL AIR
                                    </h4>
                                </div>
                                <div class="card-body">
                                    <div id="rlevel" class="row">
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="frlevel"></span>
                                                <span class="text-gray-600">cm</span>
                                            </h1>
                                        </div>
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="rstatuslevel"></span>
                                            </h1>
                                        </div>
                                    </div>
                                    <div id="glevel" style="display: none;">
                                        <figure class="highcharts-figure">
                                            <div id="levelchart"></div>
                                        </figure>
                                        <div class="text-center mt-1">
                                            <button id="tutupglevel" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="fpdflevel" style="display: none;">
                                        <div class="row align-content-center justify-content-center text-center py-1">
                                            <div class="col-lg-12" style="max-width: 400px;">
                                                <form class="user" id="formlevel">
                                                    <input type="hidden" name="tipe" value="level">
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl1" id="exampleInputEmail" aria-describedby="emailHelp">
                                                    </div>
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl2" id="exampleInputPassword">
                                                    </div>
                                                    <button id="expdflevel" class="btn btn-primary btn-user btn-block" value="expdflevel">
                                                        Export
                                                    </button>
                                                </form>
                                            </div>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutupflevel" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="tlevel" style="display: none;">
                                        <div style="height: 167px;overflow: scroll;overflow-x: hidden;">
                                            <table class="table table-bordered" id="tabellevel" width="100%" cellspacing="0">
                                                <thead>
                                                    <tr>
                                                        <th>Waktu</th>
                                                        <th>Nilai</th>
                                                        <th>Status</th>
                                                    </tr>
                                                </thead>
                                            </table>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutuptlevel" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                </div>
                                <div id="flevel" class="card-footer py-3">
                                    <div class="row d-flex flex-row align-items-center">
                                        <div class="col-lg-6">
                                            <h6 class="m-0 font-weight-bold text-primary waktulevel">
                                            </h6>
                                        </div>
                                        <div class="col-lg-6 text-xl-right">
                                            <button id="bukaglevel" class=" btn btn-sm ml-auto btn-primary shadow-sm" value="level">
                                                <i class="fas fa-chart-line fa-sm text-white-50"></i> Grafik
                                            </button>
                                            <button id="bukatlevel" class="btn btn-sm ml-auto btn-primary shadow-sm" value="level">
                                                <i class="fas fa-table fa-sm text-white-50"></i> Tabel
                                            </button>
                                            <button id="bukaflevel" class="btn btn-sm ml-auto btn-primary shadow-sm" value="level">
                                                <i class="fas fa-file-pdf fa-sm text-white-50"></i> PDF
                                            </button>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                        <div class="py-2 col-lg-6">
                            <div class="card shadow mb-4">
                                <div class="card-header py-3">
                                    <h4 class="m-0 font-weight-bold text-primary text-center">
                                        LAJU SUNGAI
                                    </h4>
                                </div>
                                <div class="card-body">
                                    <div id="rlaju" class="row">
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="frlaju"></span>
                                                <span class="text-gray-600">m/s</span>
                                            </h1>
                                        </div>
                                        <div class="col-md-6">
                                            <h1 class="text-center py-3" style="font-size: 5rem">
                                                <span class="font-weight-bold text-gray-800" id="rstatuslaju"></span>
                                            </h1>
                                        </div>
                                    </div>
                                    <div id="glaju" style="display: none;">
                                        <figure class="highcharts-figure">
                                            <div id="lajuchart"></div>
                                        </figure>
                                        <div class="text-center mt-1">
                                            <button id="tutupglaju" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="fpdflaju" style="display: none;">
                                        <div class="row align-content-center justify-content-center text-center py-1">
                                            <div class="col-lg-12" style="max-width: 400px;">
                                                <form class="user" id="formlaju">
                                                    <input type="hidden" name="tipe" value="laju">
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl1" id="exampleInputEmail" aria-describedby="emailHelp">
                                                    </div>
                                                    <div class="form-group">
                                                        <input type="date" class="form-control form-control-user" name="tgl2" id="exampleInputPassword">
                                                    </div>
                                                    <button id="expdflaju" class="btn btn-primary btn-user btn-block" value="expdflaju">
                                                        Export
                                                    </button>
                                                </form>
                                            </div>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutupflaju" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                    <div id="tlaju" style="display: none;">
                                        <div style="height: 167px;overflow: scroll;overflow-x: auto;">
                                            <table class="table table-bordered" id="tabellaju" width="100%" cellspacing="0">
                                                <thead>
                                                    <tr>
                                                        <th>Waktu</th>
                                                        <th>WaterFlow1</th>
                                                        <th>WaterFlow2</th>
                                                        <th>WaterFlow3</th>
                                                        <th>WaterFlow4</th>
                                                    </tr>
                                                </thead>
                                            </table>
                                        </div>
                                        <div class="text-center mt-1">
                                            <button id="tutuptlaju" class=" btn btn-sm ml-auto btn-primary shadow-sm">
                                                <i class="fas fa-times fa-sm text-white-50"></i> Tutup
                                            </button>
                                        </div>
                                    </div>
                                </div>
                                <div id="flaju" class="card-footer py-3">
                                    <div class="row d-flex flex-row align-items-center">
                                        <div class="col-lg-6">
                                            <h6 class="m-0 font-weight-bold text-primary waktulaju">
                                            </h6>
                                        </div>
                                        <div class="col-lg-6 text-xl-right">
                                            <button id="bukaglaju" class=" btn btn-sm ml-auto btn-primary shadow-sm" value="laju">
                                                <i class="fas fa-chart-line fa-sm text-white-50"></i> Grafik
                                            </button>
                                            <button id="bukatlaju" class="btn btn-sm ml-auto btn-primary shadow-sm" value="laju">
                                                <i class="fas fa-table fa-sm text-white-50"></i> Tabel
                                            </button>
                                            <button id="bukaflaju" class="btn btn-sm ml-auto btn-primary shadow-sm" value="laju">
                                                <i class="fas fa-file-pdf fa-sm text-white-50"></i> PDF
                                            </button>
                                        </div>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
                <!-- /.container-fluid -->
            </div>
            <!-- End of Main Content -->
            <!-- Footer -->
            <footer class="sticky-footer bg-white">
                <div class="container my-auto">
                    <div class="copyright text-center my-auto">
                        <span>Copyright &copy; siagabanjir 2022</span>
                    </div>
                </div>
            </footer>
        </div>
    </div>
    <a class="scroll-to-top rounded" href="#page-top">
        <i class="fas fa-angle-up"></i>
    </a>
    <div class="modal fade" id="logoutModal" tabindex="-1" role="dialog" aria-labelledby="exampleModalLabel" aria-hidden="true">
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h5 class="modal-title" id="exampleModalLabel">Ready to Leave?</h5>
                    <button class="close" type="button" data-dismiss="modal" aria-label="Close">
                        <span aria-hidden="true">×</span>
                    </button>
                </div>
                <div class="modal-body">
                    Select "Logout" below if you are ready to end your current session.
                </div>
                <div class="modal-footer">
                    <button class="btn btn-secondary" type="button" data-dismiss="modal">
                        Cancel
                    </button>
                    <a class="btn btn-primary" href="login.html">Logout</a>
                </div>
            </div>
        </div>
    </div>
    <script src="vendor/jquery/jquery.min.js"></script>
    <script src="vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
    <script src="vendor/jquery-easing/jquery.easing.min.js"></script>
    <script src="js/sb-admin-2.min.js"></script>
    <script src="js/firebase-app.js"></script>
    <script src="js/firebase-database.js"></script>
    <script src="js/highcharts.js"></script>
    <script src="vendor/datatables/jquery.dataTables.min.js"></script>
    <script src="vendor/datatables/dataTables.bootstrap4.min.js"></script>
    <script>
        $(document).ready(function() {

            function myFirebase() {
                var firebaseConfig = {
                    apiKey: "AIzaSyD_C-6IpuktYTCnINaGZSFwJNC7ZM3V8O0",
                    authDomain: "tasiagabanjir.firebaseapp.com",
                    // The value of `databaseURL` depends on the location of the database
                    databaseURL: "https://tasiagabanjir-default-rtdb.asia-southeast1.firebasedatabase.app",
                    projectId: "tasiagabanjir",
                    storageBucket: "tasiagabanjir.appspot.com",
                    messagingSenderId: "238856181326",
                    appId: "1:238856181326:web:938978b632b356a00a951f",
                    // For Firebase JavaScript SDK v7.20.0 and later, `measurementId` is an optional field
                    measurementId: "G-6TR03QGTVE",
                };

                firebase.initializeApp(firebaseConfig);
                var scurah = document.getElementById("frcurah");
                var slevel = document.getElementById("frlevel");
                var slaju = document.getElementById("frlaju");
                var statuscurah = document.getElementById("rstatuscurah");
                var statuslevel = document.getElementById("rstatuslevel");
                var statuslaju = document.getElementById("rstatuslaju");

                var firebaseRefcurah = firebase.database().ref("data").child("curah");
                firebaseRefcurah.on('value', function(snapshot) {
                    scurah.innerText = snapshot.val();
                })

                var firebaseReflevel = firebase.database().ref("data").child("level");
                firebaseReflevel.on('value', function(snapshot) {
                    slevel.innerText = snapshot.val();
                })

                var firebaseReflaju = firebase.database().ref("data").child("laju");
                firebaseReflaju.on('value', function(snapshot) {
                    slaju.innerText = snapshot.val();
                })

                var firebaseRefstatuscurah = firebase.database().ref("data").child("status_curah");
                firebaseRefstatuscurah.on('value', function(snapshot) {
                    statuscurah.innerText = snapshot.val();
                })

                var firebaseRefstatuslevel = firebase.database().ref("data").child("status_level");
                firebaseRefstatuslevel.on('value', function(snapshot) {
                    statuslevel.innerText = snapshot.val();
                })

                var firebaseRefstatuslaju = firebase.database().ref("data").child("status_laju");
                firebaseRefstatuslaju.on('value', function(snapshot) {
                    statuslaju.innerText = snapshot.val();
                })
            }
            myFirebase();

            function gets() {
                $.ajax({
                        type: "POST",
                        url: "./inc/process.php?p=realtime",
                        dataType: "json",
                    })
                    .done(function(data) {
                        // $(".rcurah").empty().append(data.curah)
                        // $(".rlevel").empty().append(data.level)
                        // $(".rlaju").empty().append(data.laju)
                        // $(".rstatuscurah").empty().append(data.status_curah)
                        // $(".rstatuslevel").empty().append(data.status_level)
                        // $(".rstatuslaju").empty().append(data.status_laju)
                        $(".waktucurah").empty().append(data.waktucurah)
                        $(".waktulaju").empty().append(data.waktulaju)
                        $(".waktulevel").empty().append(data.waktulevel)
                        // $(".waktuscurah").empty().append(data.time_curah)
                        // $(".waktuslaju").empty().append(data.time_laju)
                        // $(".waktuslevel").empty().append(data.time_level)
                    })
            }
            setInterval(() => {
                gets()
            }, 10000);
            gets()

            function bukagrafik(idbutton, iddivgrafik, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    var tipe = $(this).val();
                    graph(tipe);
                    console.log(tipe);
                    $("#" + iddivgrafik).css("display", "");
                    $("#" + iddivrealtime).css("display", "none");
                    $("#" + idfooter).css("display", "none");
                });
            }
            bukagrafik("bukagcurah", "gcurah", "rcurah", "fcurah")
            bukagrafik("bukaglevel", "glevel", "rlevel", "flevel")
            bukagrafik("bukaglaju", "glaju", "rlaju", "flaju")

            function tutupgrafik(idbutton, iddivgrafik, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    $("#" + iddivgrafik).css("display", "none");
                    $("#" + iddivrealtime).css("display", "");
                    $("#" + idfooter).css("display", "");
                });
            }
            tutupgrafik("tutupgcurah", "gcurah", "rcurah", "fcurah")
            tutupgrafik("tutupglevel", "glevel", "rlevel", "flevel")
            tutupgrafik("tutupglaju", "glaju", "rlaju", "flaju")

            function bukatabel(idbutton, iddivtabel, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    // var tipe = $(this).val();
                    // tabel(tipe);
                    // console.log(tipe);
                    $("#" + iddivtabel).css("display", "");
                    $("#" + iddivrealtime).css("display", "none");
                    $("#" + idfooter).css("display", "none");
                });
            }
            bukatabel("bukatcurah", "tcurah", "rcurah", "fcurah")
            bukatabel("bukatlevel", "tlevel", "rlevel", "flevel")
            bukatabel("bukatlaju", "tlaju", "rlaju", "flaju")

            function tutuptabel(idbutton, iddivtabel, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    $("#" + iddivtabel).css("display", "none");
                    $("#" + iddivrealtime).css("display", "");
                    $("#" + idfooter).css("display", "");
                });
            }
            tutuptabel("tutuptcurah", "tcurah", "rcurah", "fcurah")
            tutuptabel("tutuptlevel", "tlevel", "rlevel", "flevel")
            tutuptabel("tutuptlaju", "tlaju", "rlaju", "flaju")

            function bukaformpdf(idbutton, iddivform, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    // var tipe = $(this).val();
                    // exportpdf(tipe);
                    // console.log(tipe);
                    $("#" + iddivform).css("display", "");
                    $("#" + iddivrealtime).css("display", "none");
                    $("#" + idfooter).css("display", "none");
                });
            }
            bukaformpdf("bukafcurah", "fpdfcurah", "rcurah", "fcurah")
            bukaformpdf("bukaflaju", "fpdflaju", "rlaju", "flaju")
            bukaformpdf("bukaflevel", "fpdflevel", "rlevel", "flevel")

            function tutupformpdf(idbutton, iddivform, iddivrealtime, idfooter) {
                $("#" + idbutton).click(function(e) {
                    e.preventDefault();
                    $("#" + iddivform).css("display", "none");
                    $("#" + iddivrealtime).css("display", "");
                    $("#" + idfooter).css("display", "");
                });
            }
            tutupformpdf("tutupfcurah", "fpdfcurah", "rcurah", "fcurah")
            tutupformpdf("tutupflaju", "fpdflaju", "rlaju", "flaju")
            tutupformpdf("tutupflevel", "fpdflevel", "rlevel", "flevel")


            function exportpdf(idexport, idformpdf) {
                $("#" + idexport).click(function(e) {
                    e.preventDefault();
                    tipe = $("#" + idformpdf).find("input[name='tipe']").val();
                    if (tipe == 'curah') {
                        title = 'Curah Hujan'
                    } else if (tipe == 'level') {
                        title = 'Level Air'
                    } else if (tipe == 'laju') {
                        title = 'Laju Sungai'
                    }
                    tglawal = $("#" + idformpdf).find("input[name='tgl1']").val();
                    tglakhir = $("#" + idformpdf).find("input[name='tgl2']").val();
                    // console.log(tipe, tglawal, tglakhir)
                    location.assign("./inc/fpdf/index.php?tipe=" + tipe + "&tglawal=" + tglawal + "&tglakhir=" + tglakhir + "&title=" + title)
                });
            }

            exportpdf("expdfcurah", "formcurah")
            exportpdf("expdflaju", "formlaju")
            exportpdf("expdflevel", "formlevel")

            $('#tabelcurah').DataTable({
                'ajax': './inc/process.php?p=tabel&q=curah',
                'columns': [{
                        'data': 'waktu'
                    },
                    {
                        'data': 'value1'
                    },
                    {
                        'data': 'hujan'
                    },
                ]
            });
            $('#tabellevel').DataTable({
                'ajax': './inc/process.php?p=tabel&q=level',
                'columns': [{
                        'data': 'waktu'
                    },
                    {
                        'data': 'value1'
                    },
                    {
                        'data': 'value2'
                    },
                ]
            });
            $('#tabellaju').DataTable({
                'ajax': './inc/process.php?p=tabel&q=laju',
                'columns': [{
                        'data': 'waktu'
                    },
                    {
                        'data': 'WaterFlow1'
                    },
                    {
                        'data': 'WaterFlow2'
                    },
                    {
                        'data': 'WaterFlow3'
                    },
                    {
                        'data': 'WaterFlow4'
                    }
                ]
            });

            function graph(tipe) {
                if (tipe == 'curah') {
                    idd = 'curahchart'
                    lebel = 'tingkat curah hujan (mm)'
                    json_path = "./inc/process.php?p=grafikk&q=curah"
                    ytext = 'curah hujan (mm)'
                    sname = 'curah (mm)'
                } else if (tipe == 'level') {
                    idd = 'levelchart'
                    lebel = 'tingkat level air (cm)'
                    json_path = "./inc/process.php?p=grafikk&q=level"
                    ytext = 'level air (cm)'
                    sname = 'level (cm)'
                } else if (tipe == 'laju') {
                    idd = 'lajuchart'
                    lebel = 'tingkat laju sungai (m/s)'
                    json_path = "./inc/process.php?p=grafikk&q=laju"
                    ytext = 'laju sungai (m/s)'
                    sname = 'laju (m/s)'
                } else {
                    lebel = '?'
                    json_path = '?'
                }

                var options = {
                    title: {
                        text: null,
                    },

                    subtitle: {
                        text: lebel
                    },

                    yAxis: {
                        title: {
                            text: ytext
                        }
                    },

                    xAxis: {
                        categories: []
                    },

                    legend: {
                        layout: 'vertical',
                        align: 'right',
                        verticalAlign: 'middle'
                    },

                    plotOptions: {
                        series: {
                            label: {
                                connectorAllowed: false
                            }
                        }
                    },

                    series: [{
                        name: sname,
                        data: []
                    }],

                    responsive: {
                        rules: [{
                            condition: {
                                maxWidth: 500
                            },
                            chartOptions: {
                                legend: {
                                    layout: 'horizontal',
                                    align: 'center',
                                    verticalAlign: 'bottom'
                                }
                            }
                        }]
                    }

                }

                var options2 = {
                    title: {
                        text: null,
                    },

                    subtitle: {
                        text: lebel
                    },

                    yAxis: {
                        title: {
                            text: ytext
                        }
                    },

                    xAxis: {
                        categories: []
                    },

                    legend: {
                        layout: 'vertical',
                        align: 'right',
                        verticalAlign: 'middle'
                    },

                    plotOptions: {
                        series: {
                            label: {
                                connectorAllowed: false
                            }
                        }
                    },

                    series: [{
                        name: 'WaterFlow1',
                        data: []
                    }, {
                        name: 'WaterFlow2',
                        data: []
                    }, {
                        name: 'WaterFlow3',
                        data: []
                    }, {
                        name: 'WaterFlow4',
                        data: []
                    }],

                    responsive: {
                        rules: [{
                            condition: {
                                maxWidth: 500
                            },
                            chartOptions: {
                                legend: {
                                    layout: 'horizontal',
                                    align: 'center',
                                    verticalAlign: 'bottom'
                                }
                            }
                        }]
                    }

                }

                $.getJSON(json_path, function(json) {
                    if (tipe == 'curah' || tipe == 'level') {
                        options.xAxis.categories = json[0]['data'];
                        options.series[0].data = json[1]['data'];
                        myChart = new Highcharts.chart(idd, options);
                    } else if (tipe == 'laju') {
                        options2.xAxis.categories = json[0]['data'];
                        options2.series[0].data = json[1]['data'];
                        options2.series[1].data = json[2]['data'];
                        options2.series[2].data = json[3]['data'];
                        options2.series[3].data = json[4]['data'];
                        myChart = new Highcharts.chart(idd, options2);
                    }
                });
            }
            graph();
        });
    </script>
</body>

</html>