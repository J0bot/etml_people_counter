<?php
    require_once('./src/php/Application/DBHelper.php');
    require_once('./src/php/Application/RecordDataHandler.php');

    $database = new DBHelper();
    $recordDataHandler = new RecordDataHandler();
    $arduinos = $database->getArduinos();
    $rooms = [];
?>

<!DOCTYPE html>
<html lang="fr">
    <head>
        <meta charset="UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>Dashboard</title>

        <link href="./src/css/library/bootstrap.dark.min.css" rel="stylesheet">
        <link rel="stylesheet" href="./src/css/library/Chart.min.css">
        <link rel="stylesheet" href="./src/css/library/bootstrap-toggle.min.css">
        <link rel="stylesheet" href="./src/css/custom.css">
        
        
        
    </head>
    <body>
        <div class="modal fade" id="resumeModal" tabindex="-1" aria-labelledby="modalTitle" aria-hidden="true">
            <div class="modal-dialog modal-xl modal-dialog-centered modal-dialog-scrollable">
                <div class="modal-content">
                    <div class="modal-header">
                        <h5 class="modal-title" id="modalTitle">Default resume modal title</h5>
                    </div>
                    <div class="modal-body">
                        <canvas id="modalCanvas"></canvas>
                        <hr />
                        <?php
                            $roomRecords = []; 
                            include('./src/templates/_counter.php'); 
                        ?>
                    </div>
                    <div class="modal-footer">
                        <button type="button" class="btn btn-secondary" data-bs-dismiss="modal">Fermer</button>
                    </div>
                </div>
            </div>
        </div>

        <div class="row ml-1 mt-3">
            <div><input id="toggleCharts" type="checkbox" checked data-toggle="toggle" data-on="Temps réel" data-off="Graphiques" data-onstyle="info" data-offstyle="primary" onclick="toggleCharts()"></div>
            <div class="col"></div>
        </div>
        <div class="row row-cols-xl-3 row-cols-lg-2 row-cols-md-2 row-cols-sm-1 row-cols-1">
            <?php
                foreach($arduinos as $ardDatas) {
                    $rooms[$ardDatas['regName']]['macAddresses'][] = $ardDatas['ardMacAddress'];
                    $rooms[$ardDatas['regName']]['type'] = $ardDatas['regType'];
                    $rooms[$ardDatas['regName']]['name'] = $ardDatas['regName'];
                }

                foreach($rooms as $room) {
                    $roomRecords = $database->getRoomDatas($room['macAddresses']);
            ?>
                     <div class="col mb-3">
                        <div class="card h-100 m-3" id=<?= $room['name']?> <?php if($room['type'] === 'zone') echo('style="border-style: dotted; border-color: gray; border-width: 2px;"') ?> onclick="updateModal(this.id)">
                            <div class="card-header text-center"><h5><?= $room['name']?></h5></div>
                            <div class="card-body p-0">
                                <?php 
                                    include('./src/templates/_counter.php');
                                    include('./src/templates/_graphic.php');
                                ?>
                            </div>   
                        </div>
                    </div>
            <?php
                }
            ?>
        </div>
    </body>

    <script src="./src/js/library/jquery.min.js"></script>
    <script src="./src/js/library/bootstrap.bundle.min.js"></script>
    <script src="./src/js/library/bootstrap-toggle.min.js"></script>
    <script src="./src/js/library/Chart.bundle.min.js"></script>
    <script src="./src/js/library/hammer.min.js"></script>
    <script src="./src/js/library/chartjs-plugin-zoom.min.js"></script>
    <script src="./src/js/Application/graphicChart.js"></script>
    <script src="./src/js/counterHandler.js"></script>
    <script src="./src/js/graphicHandler.js"></script>
    <script src="./src/js/toggleHandler.js"></script>
    <script src="./src/js/modalHandler.js"></script>
</html>
