import React from "react";
import { Table } from "antd";

const S1dataSource = [
    {
        key: '1',
        number: 1,
        releaseTime: 0,
        deadline: 3,
        width: 1,
        height: 1,
    },
    {
        key: '2',
        number: 2,
        releaseTime: 2,
        deadline: 13,
        width: 1,
        height: 1,
    },
];

const S2dataSource = [
    {
        key: '1',
        number: 1,
        releaseTime: 0,
        deadline: 3,
        width: 1,
        height: 1,
    },
    {
        key: '2',
        number: 2,
        releaseTime: 2,
        deadline: 13,
        width: 1,
        height: 1,
    },
];

const S3dataSource = [
    {
        key: '1',
        number: 1,
        releaseTime: 0,
        deadline: 3,
        width: 1,
        height: 1,
    },
    {
        key: '2',
        number: 2,
        releaseTime: 2,
        deadline: 13,
        width: 1,
        height: 1,
    },
];

const S4dataSource = [
    {
        key: '1',
        number: 1,
        releaseTime: 0,
        deadline: 3,
        width: 1,
        height: 1,
    },
    {
        key: '2',
        number: 2,
        releaseTime: 2,
        deadline: 13,
        width: 1,
        height: 1,
    },
];
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
        children: <Table dataSource={S1dataSource} columns={columns} />,
    },
    {
        key: '2',
        label: 'Scenario 2',
        children: <Table dataSource={S2dataSource} columns={columns} />,
    },
    {
        key: '3',
        label: 'Scenario 3',
        children: <Table dataSource={S3dataSource} columns={columns} />,
    },
    {
        key: '4',
        label: 'Scenario 4',
        children: <Table dataSource={S4dataSource} columns={columns} />,
    },
];

export default scenarios;