<?php
    require('./src/php/Application/DBHelper.php');

    if(!empty($_GET)) {
        $database = new DBHelper();

        echo (json_encode($database->getArduinosFromRoomName($_GET['regionName'])));
    }
?>