<?php
	date_default_timezone_set('Europe/Paris');
	session_start();	
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
	<title> Réseau social </title>	
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8" xml:lang="fr-FR">
	<link rel="stylesheet" type="text/css" href="../css/layout.css" />
	<link rel="stylesheet" type="text/css" href="../css/style.css" />
	<script type=text/javascript src="../js/jquery-1.9.1.min.js"></script>
	<script type=text/javascript src="../js/likes_manage.js"></script>	
	<script type=text/javascript src="../js/profil_display.js"></script>
	<script type=text/javascript src="../js/connect.js"></script>	
</head>
<body>
	<?php include("../elements/head.php"); ?>
	
	<div id="content">
	
		<?php include("../elements/menu.php"); ?>
		
		<div id="corps">
			<?php
			if (isset($_SESSION['nom']) AND isset($_SESSION['prenom'])){
			?>
			<div id="evenement">
				<a class="evenement" href="../event/event_create.php"><img src="../medias/images/even_plus.gif" width="1%" /> <b>Créer un événement</b></a><br/>
				<?php 
				include("../event/event_display.php");
				?>
			</div>
			<?php	
				include("../message/message.php"); 
//				echo "<script>alert('".$_SESSION['id']."')</script>";
			}
			else{
				echo "<h1>Message de présentation du site pour les visiteurs</h1>";
			}
			?>
				
		</div>
	</div>
	
	<?php include("../elements/foot.php") ?>
</body>
</html>