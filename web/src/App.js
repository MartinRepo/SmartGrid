import React, { useState, useEffect } from "react";
import Selector from "./Selector/Selector";
import ScenarioCollapse from "./ScenarioCollapse/ScenarioCollapse";
import {Button, Tabs, Timeline} from "antd";
import { ClockCircleOutlined } from '@ant-design/icons';
import { renderScatter, renderBar, renderSummary } from "./Chart/Chart";
import Footer from "./Footer/Footer"
import axios from 'axios';
import "./App.css"
function App() {
    const [loading, setLoading] = useState(false);
    const [showChart, setShowChart] = useState(false);
    const [activeTabKey, setActiveTabKey] = useState('1');
    const [selectedValues, setSelectedValues] = useState([]);
    const [totalCost, setTotalCost] = useState([]);
    const [peakCost, setPeakCost] = useState([]);
    const [runningTime, setRunningTime] = useState([]);

    useEffect(() => {
        if(activeTabKey === '1' && showChart) {
            setTimeout(() => {
                renderScatter(`container-${activeTabKey}`, totalCost, "Total Power Cost");
            }, 50);
        }else if(activeTabKey === '2' && showChart) {
            setTimeout(() => {
                renderScatter(`container-${activeTabKey}`, peakCost, "Peak Power Cost");
            }, 50);
        }else if(activeTabKey === '3' && showChart) {
            setTimeout(() => {
                renderBar(`container-${activeTabKey}`, runningTime);
            }, 50);
        }else if(activeTabKey === '4' && showChart) {
            setTimeout(() => {
                renderSummary(totalCost, peakCost, runningTime);
            }, 50);
        }
    }, [activeTabKey, showChart, totalCost, peakCost, runningTime]);
    const onChange = (key) => {
        setActiveTabKey(key);
    };

    const handleSelectorChange = values => {
        setSelectedValues(values);
    };
    const handleClick = () => {
        setLoading(true);
        // axios.post('https://demo-smartgrid.tech/api/run-algorithms', {
            // selectedValues
        // })
        axios.post('http://localhost:8000/api/run-algorithms', {
            selectedValues
        })
            .then(response => {
                console.log(response.data);
                setTotalCost(response.data.TotalCost);
                setPeakCost(response.data.PeakCost);
                setRunningTime(response.data.RunningTime);
                setLoading(false);
                setShowChart(true);
            })
            .catch(error => {
                console.error('Error:', error);
                setLoading(false);
            });
    };

    const items = [
        {
            key: '1',
            label: 'Total power cost',
            children: <div id="container-1" style={{width: '80%', height: '500px' }}></div>,
        },
        {
            key: '2',
            label: 'Peak cost',
            children: <div id="container-2" style={{width: '80%', height: '500px' }}></div>,
        },
        {
            key: '3',
            label: 'Running time',
            children: <div id="container-3" style={{width: '80%', height: '500px' }}></div>,
        },
        {
            key: '4',
            label: 'Summary',
            children:
                <>
                    <div id="container-4" style={{width: '80%', height: '500px' }}> <strong>Summary for Total Power Cost</strong> </div>
                    <div id="container-5" style={{width: '80%', height: '500px' }}> <strong> Summary for Peak Power Cost </strong> </div>
                    <div id="container-6" style={{width: '80%', height: '500px' }}> <strong> Summary for Running Time </strong> </div>
                </>
        }
    ];

  return (
    <div style={{display: 'flex', justifyContent: 'center', flexDirection: 'column', alignItems: 'center'}}>
        <h1>
            SCHEDULING FOR SMART GRID
        </h1>
        <h2>
            DEMO SITE
        </h2>
        <h2>
            Scenarios Dataset Selection
        </h2>
        <Selector onChange={handleSelectorChange}/>
        {!loading ?
            <div style={{ display: 'flex', justifyContent: 'center', width: '60%', marginTop: '10px'}}>
                <Button style={{ width: '40%' }} type="primary" block disabled={selectedValues.length === 0} onClick={handleClick} > Compare! </Button>
            </div>
            :
            <div style={{ display: 'flex', justifyContent: 'center', width: '60%', marginTop: '10px'}}>
                <Button style={{ width: '40%' }} type="primary" loading/>
            </div>
        }
        <h2>
            Scenario Dataset Details
        </h2>
        <ScenarioCollapse/>
        {showChart &&
            <>
            <h2>Performance Comparison Result</h2>
            <Tabs onChange={onChange} style={{width: '60%', marginTop: '20px'}} defaultActiveKey='1' tabPosition="top" items={items} />
            </>
        }
        <h2>Project Timeline</h2>
        <Timeline mode='left'
                  style={{ width: '80%' }}
                  pending={"Website Audit & Project discussion & Dissertation writing"}
            items={[
                {
                    label: '2023-09-16',
                    children: 'Start Project, studying literatures',
                },
                {
                    label: '2023-09-26',
                    children: 'Start Project Proposal',
                },
                {
                    label: '2023-10-01',
                    children: 'Start algorithms development simply',
                },
                {
                    label: '2023-10-26',
                    color: 'green',
                    children: 'Complete Project Proposal',
                },
                {
                    label: '2023-11-02',
                    children: 'Implement algorithms detailed',
                },
                {
                    label: '2024-01-15',
                    color: 'green',
                    children: 'Complete algorithms development for specific scenario',
                },
                {
                    label: '2024-01-15',
                    children: 'Start dissertation writing',
                },
                {
                    label: '2024-03-14',
                    color: 'green',
                    children: 'Complete algorithms development for all scenarios',
                },
                {
                    label: '2024-03-14',
                    children: 'Prepare dataset for all scenarios',
                },
                {
                    label: '2024-03-20',
                    color: 'green',
                    children: 'technical testing',
                },
                {
                    label: '2024-04-01',
                    color: 'green',
                    children: 'Complete demo site, for better visualization',
                },
                {
                    label: '2024-04-06',
                    color: 'red',
                    dot: <ClockCircleOutlined />,
                    children: <p>Deploy demo site <a href='https://demo-smartgrid.tech'>https://demo-smartgrid.tech</a></p>,
                },
                // {
                //     label: '2024-04-07',
                //     color: '#00CCFF',
                //     dot: <SmileOutlined />,
                //     children: 'Congrats! 🎉',
                // },
            ]}
        />
        <Footer/>
    </div>
  );
}

export default App;
