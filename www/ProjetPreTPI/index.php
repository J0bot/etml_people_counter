<?php
include('./src/php/route.php');

Route::add('/', function() {
    header('Location: ./dashboard');
});

Route::add('/dashboard', function() {
    include('./src/php/index.php');
});

Route::add('/api/getarduinos', function() {
    include('./src/php/API/getArduinos.php');
});

Route::add('/api/getArduinosFromRegionName', function() {
    include('./src/php/API/getArduinosFromRegionName.php');
});

Route::add('/api/getroomrecords', function() {
    include('./src/php/API/getRoomRecords.php');
});

Route::add('/api/deleteall', function() {
    include('./src/php/API/deleteAllRecord.php');
});

Route::add('/api/checkPassword', function() {
    include('./src/php/API/checkPassword.php');
});

Route::add('/api/addrecord', function() {
    include('./src/php/API/addRecord.php');
}, 'post');

Route::run('/');
?>