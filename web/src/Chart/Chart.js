import { Chart } from '@antv/g2';
const renderScatter = (containerId, dataSource, yAxis) => {
    const chart = new Chart({
        container: containerId,
        autoFit: true,
    });

    chart.point()
        .data(dataSource)
        .encode('x', 'dataset')
        .encode('y', yAxis)
        .encode('color', 'algorithm')
        .encode('shape', 'hexagon');

    chart.render();
}

const renderBar = (containerId, dataSource) => {
    const chart = new Chart({
        container: containerId,
        autoFit: true,
    });

    chart.interval()
        .data(dataSource)
        .encode('x', 'dataset')
        .encode('y', 'Running Time /µs')
        .encode('color', 'algorithm')
        .transform({ type: 'dodgeX' })
        .interaction('elementHighlight', { background: true });

    chart.render();
}

function processData(data, name) {
    const algorithms = [...new Set(data.map(item => item.algorithm))];
    let processedData = [];
    algorithms.forEach(algorithm => {
        const costs = data.filter(item => item.algorithm === algorithm).map(item => item[name]);
        const maxCost = Math.max(...costs);
        const minCost = Math.min(...costs);
        processedData.push({ algorithm, max: maxCost, min: minCost });
    });
    return processedData;
}
const renderSummary = (totalCost, peakCost, runningTime) => {
    let processedData = processData(totalCost, 'Total Power Cost');

    let chart = new Chart({
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

    processedData = processData(peakCost, 'Peak Power Cost');
    chart = new Chart({
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

    processedData = processData(runningTime, 'Running Time /µs');
    chart = new Chart({
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
}
export { renderScatter, renderBar, renderSummary };