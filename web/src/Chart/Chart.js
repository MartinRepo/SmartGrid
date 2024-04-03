import { Chart } from '@antv/g2';
const renderScatter = (containerId, dataPath, yAxis) => {
    const chart = new Chart({
        container: containerId,
        autoFit: true,
    });

    chart.point()
        .data({type: "fetch", value: dataPath})
        .encode('x', 'dataset')
        .encode('y', yAxis)
        .encode('color', 'algorithm')
        .encode('shape', 'hexagon');

    chart.render();
}

const renderBar = (containerId, dataPath) => {
    const chart = new Chart({
        container: containerId,
        autoFit: true,
    });

    chart.interval()
        .data({type: "fetch", value: dataPath})
        .encode('x', 'dataset')
        .encode('y', 'Running Time /ms')
        .encode('color', 'algorithm')
        .transform({ type: 'dodgeX' })
        .interaction('elementHighlight', { background: true });

    chart.render();
}

const renderSummary = () => {
    fetch('./TotalPowerCost.json')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            const algorithms = [...new Set(data.map(item => item.algorithm))];
            let processedData = [];
            algorithms.forEach(algorithm => {
                const costs = data.filter(item => item.algorithm === algorithm).map(item => item['Total Power Cost']);
                const maxCost = Math.max(...costs);
                const minCost = Math.min(...costs);
                processedData.push({ algorithm, max: maxCost, min: minCost });
            });
            const chart = new Chart({
                container: 'container-4',
                autoFit: true,
            });
            chart.interval()
                .data(processedData)
                .encode('x', 'algorithm')
                .encode('y', ['min', 'max'])
                .encode('color', 'algorithm')
                .axis('y', { labelFormatter: '~s' })
                .tooltip(['min', 'max']);

            chart.render();
        })
        .catch(error => {
            console.error('There has been a problem with your fetch operation:', error);
        });

    fetch('./PeakPowerCost.json')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            const algorithms = [...new Set(data.map(item => item.algorithm))];
            let processedData = [];
            algorithms.forEach(algorithm => {
                const costs = data.filter(item => item.algorithm === algorithm).map(item => item['Peak Power Cost']);
                const maxCost = Math.max(...costs);
                const minCost = Math.min(...costs);
                processedData.push({ algorithm, max: maxCost, min: minCost });
            });
            const chart = new Chart({
                container: 'container-5',
                autoFit: true,
            });
            chart.interval()
                .data(processedData)
                .encode('x', 'algorithm')
                .encode('y', ['min', 'max'])
                .encode('color', 'algorithm')
                .axis('y', { labelFormatter: '~s' })
                .tooltip(['min', 'max']);

            chart.render();
        })
        .catch(error => {
            console.error('There has been a problem with your fetch operation:', error);
        });

    fetch('./RunningTime.json')
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            const algorithms = [...new Set(data.map(item => item.algorithm))];
            let processedData = [];
            algorithms.forEach(algorithm => {
                const costs = data.filter(item => item.algorithm === algorithm).map(item => item['Running Time /ms']);
                const maxCost = Math.max(...costs);
                const minCost = Math.min(...costs);
                processedData.push({ algorithm, max: maxCost, min: minCost });
            });
            const chart = new Chart({
                container: 'container-6',
                autoFit: true,
            });
            chart.interval()
                .data(processedData)
                .encode('x', 'algorithm')
                .encode('y', ['min', 'max'])
                .encode('color', 'algorithm')
                .axis('y', { labelFormatter: '~s' })
                .tooltip(['min', 'max'])

            chart.render();
        })
        .catch(error => {
            console.error('There has been a problem with your fetch operation:', error);
        });
}
export { renderScatter, renderBar, renderSummary };