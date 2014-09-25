<!DOCTYPE html>
<html lang="fr">
<head>
    <title>Factorielle</title>
</head>
<body>
  <fieldset>
    <legend>html :</legend>
    <h1>Factorielle</h1>
  </fieldset>

  <fieldset>
    <legend>php :</legend>
<?php
function fact($n){
  if ($n==0) 
    return 1;
  else 
    return $n*fact($n-1);
}

if (isset($_GET['n']))// && ereg('^[0-9]+$',$_GET['n']))
  echo "Le resultat de la factorielle de {$_GET['n']} est : ".fact((int)$_GET['n'])."<br/>";
else
  echo "Tapez un entier !";
?>
  <form action="<?php echo $_SERVER['PHP_SELF']; ?>" method="get">
  </fieldset>
  <fieldset>
    <legend>html :</legend>
  <input type="number" name="n"  pattern="\d+" placeholder="Tapez un entier" required>
  <input type="submit" value="Calculer">
  </fieldset>
</form>
</body>
</html>
