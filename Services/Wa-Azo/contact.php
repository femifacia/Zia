<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Library - Page d'accueil</title>
    <link
        rel="stylesheet"
    >
</head>
<body >
    <div>
    <?php include_once('header.php'); ?>
        <h4>Contactez nous</h4>
        <form>
            <div >
                <label for="email" >Email</label>
                <input type="email" 
                 id="email" name="email" aria-describedby="email-help">  
            </div>
            <div >
                <label for="message" >Votre message</label>
                <textarea 
                  id="message" name="textarea"></textarea>
            </div>
            <button type="submit" >Envoyer</button>
        </form>
        <br />
    </div>
    <?php include_once('footer.php'); ?>
</body>
</html>