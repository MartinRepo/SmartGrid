import React from "react";
import { Table } from "antd";
import { Collapse } from "antd";

const S11dataSource = [
    {
        key: '1',
        number: 1,
        releaseTime: 1,
        deadline: 14,
        width: 1,
        height: 1,
    },
    {
        key: '2',
        number: 2,
        releaseTime: 0,
        deadline: 2,
        width: 1,
        height: 1,
    },
    {
        key: '3',
        number: 3,
        releaseTime: 3,
        deadline: 5,
        width: 1,
        height: 1,
    },
    {
        key: '4',
        number: 4,
        releaseTime: 4,
        deadline: 8,
        width: 1,
        height: 1,
    },
    {
        key: '5',
        number: 5,
        releaseTime: 5,
        deadline: 13,
        width: 1,
        height: 1,
    },
    {
        key: '6',
        number: 6,
        releaseTime: 6,
        deadline: 8,
        width: 1,
        height: 1,
    },
    {
        key: '7',
        number: 7,
        releaseTime: 7,
        deadline: 8,
        width: 1,
        height: 1,
    },
    {
        key: '8',
        number: 8,
        releaseTime: 9,
        deadline: 10,
        width: 1,
        height: 1,
    },
    {
        key: '9',
        number: 9,
        releaseTime: 10,
        deadline: 11,
        width: 1,
        height: 1,
    },
    {
        key: '10',
        number: 10,
        releaseTime: 11,
        deadline: 13,
        width: 1,
        height: 1,
    },
    {
        key: '11',
        number: 11,
        releaseTime: 12,
        deadline: 14,
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

const s1DataSource = [
    {
        key: '1',
        label: 'Dataset 1',
        children: <Table dataSource={S11dataSource} columns={columns} />,
    },
    {
        key: '2',
        label: 'Dataset 2',
        children: <Table dataSource={S11dataSource} columns={columns} />,
    },
];

const s2DataSource = [
    {
        key: '1',
        label: 'Dataset 1',
        children: <Table dataSource={S2dataSource} columns={columns} />,
    },
    {
        key: '2',
        label: 'Dataset 2',
        children: <Table dataSource={S2dataSource} columns={columns} />,
    },
];

const s3DataSource = [
    {
        key: '1',
        label: 'Dataset 1',
        children: <Table dataSource={S3dataSource} columns={columns} />,
    },
    {
        key: '2',
        label: 'Dataset 2',
        children: <Table dataSource={S3dataSource} columns={columns} />,
    },
];

const s4DataSource = [
    {
        key: '1',
        label: 'Dataset 1',
        children: <Table dataSource={S4dataSource} columns={columns} />,
    },
    {
        key: '2',
        label: 'Dataset 2',
        children: <Table dataSource={S4dataSource} columns={columns} />,
    },
];

const scenarios = [
    {
        key: '1',
        label: 'Scenario 1',
        children: <Collapse accordion defaultActiveKey="1" items={s1DataSource} />,
    },
    {
        key: '2',
        label: 'Scenario 2',
        children: <Collapse accordion defaultActiveKey="1" items={s2DataSource} />,
    },
    {
        key: '3',
        label: 'Scenario 3',
        children: <Collapse accordion defaultActiveKey="1" items={s3DataSource} />,
    },
    {
        key: '4',
        label: 'Scenario 4',
        children: <Collapse accordion defaultActiveKey="1" items={s4DataSource} />,
    },
];

export default scenarios;