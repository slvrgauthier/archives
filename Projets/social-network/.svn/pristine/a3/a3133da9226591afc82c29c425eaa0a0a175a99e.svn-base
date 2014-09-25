<div id="head">
	<h3> SocialNet, le pouvoir du socialWeb... </h3>
	<div id="member">
		<?php
		if (isset($_SESSION['nom']) AND isset($_SESSION['prenom'])){
		?>
		<form method="post" action="../member/disconnection.php">
			<input type=submit id="disconnect" name="disconnect" value="Se déconnecter" />
		</form>
		<?php 
			echo "<span style='color:grey'>Bonjour ".$_SESSION['nom']." ".$_SESSION['prenom']."</span>"; 
		?>
		<?php
		}
		else{
			include("../member/connection.php"); 
		}
		?>
	</div>
</div>