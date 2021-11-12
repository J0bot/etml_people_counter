function loadAllCharts() {
    $.ajax({
        url: './api/getarduinos',
        success: function(result) {
            regionMacAddresses = [];
            JSON.parse(result).forEach(ardData => {
                if (typeof regionMacAddresses[ardData.regName] == 'undefined') {
                    regionMacAddresses[ardData.regName] = [];
                }

                regionMacAddresses[ardData.regName] = regionMacAddresses[ardData.regName].concat(ardData.ardMacAddress);
            });
            Object.entries(regionMacAddresses).forEach(roomData => {
                loadOneChart(roomData);
            });
        }
    });
}

function loadOneChart(roomData, canvasId = null, resume = true) {
    $.ajax({
        url: './api/getroomrecords',
        type: 'GET',
        data: 'macAddress=' + JSON.stringify(roomData[1]),
        success: function(result) {
            data = [];
            counter = 0
            Object.entries(JSON.parse(result)).forEach(record => {
                if (record[1].recType == 'entry') {
                    data = data.concat({
                        x: Date.parse(record[1].recDate),
                        y: ++counter,
                    });
                } else {
                    data = data.concat({
                        x: Date.parse(record[1].recDate),
                        y: --counter,
                    });
                }
            });
            new GraphicChart(canvasId ?? roomData[0]+'Canvas', roomData[0], 'line', data, null, resume);
        }
    });
}