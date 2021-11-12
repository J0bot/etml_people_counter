class GraphicChart {

    gradient;
    canvas;

    constructor(canvasId, regionName, type = null, data = null, options = null, resume = false) {
        this.canvas = document.getElementById(canvasId).getContext("2d");

        this.gradient = this.canvas.createLinearGradient(0, 0, 0, 250);
        this.gradient.addColorStop(0, '#20aff7');
        this.gradient.addColorStop(1, '#282828');

        return this.getGraphic(regionName, type, data, options, resume);
    }

    getGraphic(regionName, type, data, options, resume) {
        return new Chart(this.canvas, {
            type: type ?? 'line',
            data: {
                datasets: [{
                    label: `Présence en ${regionName}`,
                    data: data ?? [{
                        x: Date.parse('2021-02-01T08:00:00'),
                        y: 1,
                    }, {
                        x: Date.parse('2021-02-01T08:30:00'),
                        y: 120,
                    }, {
                        x: Date.parse('2021-02-01T09:00:00'),
                        y: 50,
                    }, {
                        x: Date.parse('2021-02-01T09:30:00'),
                        y: 0,
                    }],
                    backgroundColor: this.gradient,
                    borderColor: '#2290c7',
                    lineTension: 0,
                }],
            },
            options: options ?? {
                scales: {
                    xAxes: [{
                        type: 'time',
                        ticks: {
                            source: 'auto',
                        },
                        gridLines: {
                            display: false,
                        },
                        time: {
                            unit: 'minute',
                            tooltipFormat: 'H:mm:ss',
                            displayFormats: {
                                minute: 'H:mm'
                            },
                        },
                    }],
                    yAxes: [{
                        gridLines: {
                            display: true,
                            color: '#5e5e5e'
                        },
                        ticks: {
                            stepSize: 1,
                            beginAtZero: true,
                        },
                    }],
                },
				plugins: {
                    zoom: {
                        pan: {
                            enabled: !resume,
                            mode: 'xy'
                        },
                        zoom: {
                            enabled: !resume,
                            mode: 'xy',
                        },
                    },
                },
                legend: {
                    display: false,
                },
                elements: {
                    point: {
                        borderWidth: 2,
                        borderColor: '#236ba6',
                        backgroundColor: '#236ba6',
                    },
                },
            },
        });
    }
}
