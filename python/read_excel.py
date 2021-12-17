#!/usr/bin/python
# -*-coding:utf-8
import pandas as pd
import datetime


def getExcelData(filename, fields, date_field):
    io = pd.read_excel(filename, "Sheet1", usecols=fields)
    return io.loc[io[date_field] >= (datetime.datetime.now() - datetime.timedelta(days=1)).strftime("%Y-%m-%d")]


def main():
    filename = r"C:\Users\Administrator\Desktop\test.xls"
    print(getExcelData(filename, "A:F", "field1"))

if __name__ == "__main__":
    main()
