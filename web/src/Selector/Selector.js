import React from 'react';
import { Select, Space } from 'antd';
import Options from './DataSource';
const Selector = ({onChange}) => (
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
            defaultValue={[]}
            onChange={(values) => {
                onChange(values);
            }}
            options={Options}
        />
    </Space>
);
export default Selector;