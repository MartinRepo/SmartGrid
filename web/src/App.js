import React, { useState, useEffect } from "react";
import Selector from "./Selector/Selector";
import ScenarioCollapse from "./ScenarioCollapse/ScenarioCollapse";
import { Button, Tabs } from "antd";
import { renderScatter, renderBar, renderSummary } from "./Chart/Chart";
function App() {
    const [loading, setLoading] = useState(false);
    const [showChart, setShowChart] = useState(false);
    const [activeTabKey, setActiveTabKey] = useState('1');
    useEffect(() => {
        if(activeTabKey === '1' && showChart) {
            setTimeout(() => {
                renderScatter(`container-${activeTabKey}`, "./TotalPowerCost.json", "Total Power Cost");
            }, 50);
        }else if(activeTabKey === '2' && showChart) {
            setTimeout(() => {
                renderScatter(`container-${activeTabKey}`, "./PeakPowerCost.json", "Peak Power Cost");
            }, 50);
        }else if(activeTabKey === '3' && showChart) {
            setTimeout(() => {
                renderBar(`container-${activeTabKey}`, "./RunningTime.json");
            }, 50);
        }else if(activeTabKey === '4' && showChart) {
            setTimeout(() => {
                renderSummary();
            }, 50);
        }
    }, [activeTabKey, showChart]);
    const onChange = (key) => {
        setActiveTabKey(key);
    };

    const handleClick = () => {
        setLoading(true);
        setTimeout(() => {
            setLoading(false);
            setShowChart(true);
        }, 2000); // 2000毫秒后执行
    };

    const items = [
        {
            key: '1',
            label: 'Total power cost',
            children: <div id="container-1" style={{width: '80%', height: '300px' }}></div>,
        },
        {
            key: '2',
            label: 'Peak cost',
            children: <div id="container-2" style={{width: '80%', height: '300px' }}></div>,
        },
        {
            key: '3',
            label: 'Running time',
            children: <div id="container-3" style={{width: '80%', height: '300px' }}></div>,
        },
        {
            key: '4',
            label: 'Summary',
            children:
                <>
                    <div id="container-4" style={{width: '80%', height: '300px' }}> <strong>Summary for Total Power Cost</strong> </div>
                <div id="container-5" style={{width: '80%', height: '300px' }}> <strong> Summary for Peak Power Cost </strong> </div>
                <div id="container-6" style={{width: '80%', height: '300px' }}> <strong> Summary for Running Time </strong> </div>
                </>
        }
    ];

  return (
    <div style={{display: 'flex', justifyContent: 'center', flexDirection: 'column', alignItems: 'center'}}>
        <h1>
            Scheduling for Smart Grid (Demo Site)
        </h1>
        <h2>
            Choose some scenarios to compare
        </h2>
        <Selector/>
        {!loading ?
            <div style={{ display: 'flex', justifyContent: 'center', width: '60%', marginTop: '10px'}}>
                <Button style={{ width: '40%' }} type="primary" block onClick={handleClick} > Compare! </Button>
            </div>
            :
            <div style={{ display: 'flex', justifyContent: 'center', width: '60%', marginTop: '10px'}}>
                <Button style={{ width: '40%' }} type="primary" loading/>
            </div>
        }
        <h2>
            Check all of scenarios below
        </h2>
        <ScenarioCollapse/>
        {showChart && <Tabs onChange={onChange} style={{width: '60%', marginTop: '20px'}} defaultActiveKey='1' tabPosition="top" items={items} />}
    </div>
  );
}

export default App;
