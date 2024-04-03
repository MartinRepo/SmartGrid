import React from 'react';
import { Select, Space } from 'antd';

// options are scenario data
const options = [
    {
        label: 'scenario 1',
        value: 'scenario 1',
    },
    {
        label: 'scenario2',
        value: 'scenario 2',
    },
    {
        label: 'scenario 3',
        value: 'scenario 3',
    },
    {
        label: 'scenario 4',
        value: 'scenario 4',
    },
];
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
            defaultValue={['scenario 1', 'scenario 2']}
            onChange={handleChange}
            options={options}
        />
    </Space>
);
export default Selector;