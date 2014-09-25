<?php
	date_default_timezone_set('Europe/Paris');
	session_start();	
?>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
<head>
	<title> Créer un événement </title>	
	<meta http-equiv="Content-Type" content="text/html;charset=utf-8" xml:lang="fr-FR">
	<link rel="stylesheet" type="text/css" href="../css/layout.css" />
	<link rel="stylesheet" type="text/css" href="../css/style.css" />
	<script type=text/javascript src="../js/calendarDateInput.js"></script>
</head>
<body>
	<?php include("../elements/head.php"); ?>
	
	<div id="content">
	
		<?php include("../elements/menu.php"); ?>
		
		<div id="corps">
			<h2>Créer un événement</h2>
			<form method=post action="event_post.php">
				Nom de l'événement <input type=text name="nom_even" /> *<br/><br/>
				Lieu de l'événement <input type=text name="lieu_even" /><br/><br/>
				Date de l'événement <script>DateInput('orderdate', true,'DD-MON-YYYY')</script><br/>
				Description <textarea name="desc_even"></textarea><br/><br/>
				<input type=submit /><br/><br/><br/>
				Participants
				<ul id="liste_participants">
				</ul>
			</form>
			<br/><br/>
			<i>* Champs obligatoires</i>
		</div>
		
	</div>
	
	<?php include("../elements/foot.php") ?>
</body>
</html>