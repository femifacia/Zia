<!-- index.php -->
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Library - Page d'accueil</title>
    <link
        rel="stylesheet"
    >
</head>
<body>
    <div >
    <?php include_once('header.php'); ?>
    <br> 
        <h3>Nos Auteurs</h3>
        <?php
            include_once('functions.php');
        ?>
        <?php for ($i = 0; $i < count($writers); $i++) {
        echo our_writers($writers[$i]);
        echo  '<br>';
    } ?>
    <?php include_once('footer.php'); ?>
</body>
</html>