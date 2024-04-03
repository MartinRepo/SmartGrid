import React from 'react';
import { Select, Space } from 'antd';
import Options from './DataSource';
const handleChange = (value) => {
    console.log(`selected ${value}`);
};
const Selector = () => (
    <Space
        style={{
            width: '60%',
        }}
        direction="vertical"
    >
        <Select
            mode="multiple"
            allowClear
            style={{
                width: '100%',
            }}
            placeholder="Please select"
            defaultValue={['scenario 1 dataset 1', 'scenario 2 dataset 1']}
            onChange={handleChange}
            options={Options}
        />
    </Space>
);
export default Selector;