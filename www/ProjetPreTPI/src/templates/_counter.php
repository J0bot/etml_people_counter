<div class="counter">  
    <div class="row p-3 h-100">
        <div class="col pt-4 my-auto">
            <div class="text-center text-success">
                <img class="icon-secondary" src="./assets/icons/arrow-right-green.svg" alt="Entries icon">
                <h6 class="count entry entry-color"><?= $recordDataHandler->extractEntriesCount($roomRecords) ?></h6>
                <h6 class="count-text entry-color">Entrées</h6>
            </div>
        </div>
        <div class="col-4 my-auto">
            <div class="text-center text-info">
                <img class="icon-primary" src="./assets/icons/people-fill.svg" alt="Current icon">
                <h6 class="count current current-color"><?= $recordDataHandler->extractCurrentsCount($roomRecords) ?></h6>
                <h6 class="count-text current-color">À l'intérieur</h6>
            </div>
        </div>
        <div class="col pt-4 my-auto">
            <div class="text-center text-danger ">
                <img class="icon-secondary" src="./assets/icons/arrow-right-red.svg" alt="Exits icon">
                <h6 class="count exit exit-color"><?= $recordDataHandler->extractExitsCount($roomRecords) ?></h6>
                <h6 class="count-text exit-color">Sorties</h6>
            </div>
        </div>
    </div>
</div>