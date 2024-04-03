import React from 'react';
import { Collapse } from 'antd';
import scenarios from './DataSource';

const ScenarioCollapse = () => {
    const onChange = (key) => {
        console.log(key);
    };
    return <Collapse accordion style={{width: '60%'}} items={scenarios} defaultActiveKey={['1']} onChange={onChange} />;
};
export default ScenarioCollapse;