<?php
require './assets/inc/function.php';
?>
<!DOCTYPE html>
<html>

<head>
	<meta http-equiv="X-UA-Compatible" content="IE=edge,chrome=1" />
	<title>Data Sensor</title>
	<meta content='width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=0, shrink-to-fit=no' name='viewport' />
	<link rel="stylesheet" href="assets/css/bootstrap.min.css">
	<link rel="stylesheet" href="https://fonts.googleapis.com/css?family=Nunito:200,200i,300,300i,400,400i,600,600i,700,700i,800,800i,900,900i">
	<link rel="stylesheet" href="https://maxst.icons8.com/vue-static/landings/line-awesome/line-awesome/1.3.0/css/line-awesome.min.css">
	<link rel="stylesheet" href="assets/css/ready.css">
	<link rel="stylesheet" href="assets/css/demo.css">
	<script>
		var refreshId = setInterval(function()

			{

				$('#on').load($('#on').attr("data-content"));

			}, 5000);
	</script>
</head>

<body>
	<div class="wrapper">
		<div class="main-header" style="background-color: #ffe4e1;">
			<div class="logo-header">
				<a href="javascript:;" onclick="changeContent('realtime.php')" class="logo">
					Data Sensor
				</a>
				<button class="navbar-toggler sidenav-toggler ml-auto" type="button" data-toggle="collapse" data-target="collapse" aria-controls="sidebar" aria-expanded="false" aria-label="Toggle navigation">
					<span class="navbar-toggler-icon"></span>
				</button>
				<button class="topbar-toggler more"><i class="la la-ellipsis-v"></i></button>
			</div>
			<nav class="navbar navbar-header navbar-expand-lg" style="background-color: #ffbcd9;">
				<div class="container-fluid">
					<ul class="navbar-nav topbar-nav ml-md-auto align-items-center">

						<li class="nav-item">
							<p class="nav-link">Politeknik Negeri Semarang</p>
						</li>
					</ul>
				</div>
			</nav>
		</div>
		<div class="sidebar">
			<div class="scrollbar-inner sidebar-wrapper">
				<ul class="nav">
					<li class="nav-item">
						<a href="javascript:;" onclick="changeContent('realtime.php')">
							<i class="la la-desktop"></i>
							<p>Dashboard</p>
						</a>
					</li>
					<li class="nav-item">
						<a href="javascript:;" onclick="changeContent('tabel.php')">
							<i class="la la-th"></i>
							<p>Tables</p>
						</a>
					</li>
					<li class="nav-item">
						<a href="javascript:;" onclick="changeContent('grafik.php')">
							<i class="las la-chart-area"></i>
							<p>Grafik Data Sensor</p>
						</a>
					</li>
				</ul>
			</div>
		</div>
		<div class="main-panel">
			<div class="content" id="on" data-content="realtime.php">
			</div>
			<footer class="footer">
				<div class="container-fluid">
					<nav class="pull-left">
						<ul class="nav">
							<li class="nav-item">
								<a class="nav-link" target="_blank" href="https://www.polines.ac.id/">
									Politeknik Negeri Semarang
								</a>
							</li>
						</ul>
					</nav>
					<div class="copyright ml-auto">
						2021, Design by <span style="color:#ff1493;">Annisa Bunga Salsabila</span></a>
					</div>
				</div>
			</footer>
		</div>
	</div>
</body>
<script src="assets/js/core/jquery.3.2.1.min.js"></script>
<script src="assets/js/plugin/jquery-ui-1.12.1.custom/jquery-ui.min.js"></script>
<script src="assets/js/core/popper.min.js"></script>
<script src="assets/js/core/bootstrap.min.js"></script>
<script src="assets/js/plugin/bootstrap-toggle/bootstrap-toggle.min.js"></script>
<script src="assets/js/plugin/jquery-scrollbar/jquery.scrollbar.min.js"></script>
<script src="assets/js/ready.min.js"></script>
<script src="assets/js/demo.js"></script>

<script type="text/javascript" src="https://cdn.jsdelivr.net/npm/chart.js"></script>
<script>
	function changeContent(content) {
		$('#on').attr('data-content', content);
		$('#on').load($('#on').attr('data-content'));
	}
</script>

</html>