import React, {useState} from "react";
import { Table, Collapse, Button } from "antd";
function Scenarios() {
    const [loading1, setLoading1] = useState(false);
    const [loading2, setLoading2] = useState(false);
    const [loading3, setLoading3] = useState(false);
    const [loading4, setLoading4] = useState(false);

    const [S1dataSource, setS1dataSource] = useState([]);
    const [S2dataSource, setS2dataSource] = useState([]);
    const [S3dataSource, setS3dataSource] = useState([]);
    const [S4dataSource, setS4dataSource] = useState([]);

    function generateRandomData(numEntries, type) {
        const dataSource = [];

        for (let i = 1; i <= numEntries; i++) {
            // Randomly generate width and height between 1 and 3 (you can adjust these values)
            let width;
            let height;
            if(type === 1) {
                width = 1;
                height = 1;
            } else if (type === 2) {
                width = 1;
                height = Math.floor(Math.random() * 3) + 1;
            } else if (type === 3) {
                width = Math.floor(Math.random() * 3) + 1;
                height = 1;
            } else if (type === 4) {
                width = Math.floor(Math.random() * 3) + 1;
                height = Math.floor(Math.random() * 3) + 1;
            }
            // Generate releaseTime randomly within a realistic range (e.g., 0 to 10)
            const releaseTime = Math.floor(Math.random() * 11);

            // Ensure deadline - releaseTime >= width by setting deadline accordingly
            const deadline = releaseTime + width + Math.floor(Math.random() * 10); // Adding random value to ensure diversity

            // Create an object for each entry
            dataSource.push({
                key: i.toString(),
                number: i,
                releaseTime: releaseTime,
                deadline: deadline,
                width: width,
                height: height
            });
        }

        return dataSource;
    }

    function handleClick(type) {
        switch (type) {
            case 1:
                setLoading1(true);
                setTimeout(() => {
                    const newDatasets = [];
                    for (let i = 0; i < 10; i++) {
                        newDatasets.push(generateRandomData(11, 1));
                    }
                    setS1dataSource(newDatasets);
                    setLoading1(false);
                }, 1000);
                break;
            case 2:
                setLoading2(true);
                setTimeout(() => {
                    const newDatasets = [];
                    for (let i = 0; i < 10; i++) {
                        newDatasets.push(generateRandomData(11, 2));
                    }
                    setS2dataSource(newDatasets);
                    setLoading2(false);
                }, 1000);
                break;
            case 3:
                setLoading3(true);
                setTimeout(() => {
                    const newDatasets = [];
                    for (let i = 0; i < 10; i++) {
                        newDatasets.push(generateRandomData(11, 3));
                    }
                    setS3dataSource(newDatasets);
                    setLoading3(false);
                }, 1000);
                break;
            case 4:
                setLoading4(true);
                setTimeout(() => {
                    const newDatasets = [];
                    for (let i = 0; i < 10; i++) {
                        newDatasets.push(generateRandomData(11, 4));
                    }
                    setS4dataSource(newDatasets);
                    setLoading4(false);
                }, 1000);
                break;
            default:
                break;
        }
    }

    const columns = [
        {
            title: 'Job No',
            dataIndex: 'number',
            key: 'number',
        },
        {
            title: 'Release time',
            dataIndex: 'releaseTime',
            key: 'releaseTime',
        },
        {
            title: 'Deadline',
            dataIndex: 'deadline',
            key: 'deadline',
        },
        {
            title: 'Duration',
            dataIndex: 'width',
            key: 'width',
        },
        {
            title: 'Power cost',
            dataIndex: 'height',
            key: 'height',
        },
    ];

    const scenarios = [
        {
            key: '1',
            label: 'Scenario 1',
            children: <>
                <strong>unit duration, unit power cost</strong>
                <Collapse accordion>
                    {S1dataSource.map((dataSource, index) => (
                        <Collapse.Panel header={`Dataset ${index + 1}`} key={index}>
                            <Table dataSource={dataSource} columns={columns} />
                        </Collapse.Panel>
                    ))}
                </Collapse>
                <br />
                <Button loading={loading1} onClick={() => handleClick(1)}>Generate data!</Button>
            </>,
        },
        {
            key: '2',
            label: 'Scenario 2',
            children: <>
                <strong>unit duration, arbitrary power cost</strong>
                <Collapse accordion>
                    {S2dataSource.map((dataSource, index) => (
                        <Collapse.Panel header={`Dataset ${index + 1}`} key={index}>
                            <Table dataSource={dataSource} columns={columns} />
                        </Collapse.Panel>
                    ))}
                </Collapse>
                <br />
                <Button loading={loading2} onClick={() => handleClick(2)}>Generate data!</Button>
            </>,
        },
        {
            key: '3',
            label: 'Scenario 3',
            children: <>
                <strong>arbitrary duration, unit power cost</strong>
                <Collapse accordion>
                    {S3dataSource.map((dataSource, index) => (
                        <Collapse.Panel header={`Dataset ${index + 1}`} key={index}>
                            <Table dataSource={dataSource} columns={columns} />
                        </Collapse.Panel>
                    ))}
                </Collapse>
                <br />
                <Button loading={loading3} onClick={() => handleClick(3)}>Generate data!</Button>
            </>,
        },
        {
            key: '4',
            label: 'Scenario 4',
            children: <>
                <strong>arbitrary duration, arbitrary power cost</strong>
                <Collapse accordion>
                    {S4dataSource.map((dataSource, index) => (
                        <Collapse.Panel header={`Dataset ${index + 1}`} key={index}>
                            <Table dataSource={dataSource} columns={columns} />
                        </Collapse.Panel>
                    ))}
                </Collapse>
                <br />
                <Button loading={loading4} onClick={() => handleClick(4)}>Generate data!</Button>
            </>,
        },
    ];
    return <Collapse style={{width: '60%'}} defaultActiveKey={['1']} accordion>{scenarios.map(scenario => (
        <Collapse.Panel header={scenario.label} key={scenario.key}>
            {scenario.children}
        </Collapse.Panel>
    ))}
    </Collapse>;
}
export default Scenarios;