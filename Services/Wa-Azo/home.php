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
        <h3>Nos Best Sellers</h3>
        <?php
            include_once('functions.php');
        ?>
        <?php for ($i = 0; $i < count($mybooks); $i++) {
        echo our_books($mybooks[$i]);
        echo  '<br>';
    } ?>
    <?php include_once('footer.php'); ?>
</body>