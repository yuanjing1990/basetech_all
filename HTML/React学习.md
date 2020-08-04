# 环境安装
React 是一个用于构建用户界面的 JAVASCRIPT 库，需要node.js环境，保证node.js安装的情况下执行以下命令
```
npm install -g cnpm --registry=https://registry.npm.taobao.org
npm config set registry https://registry.npm.taobao.org
```
之后就可以使用cnpm install [module]安装模块了（npm替换成cnpm了，因为npm使用外国地址比较慢）。

之后就可以安装create-react-app了，使用create-react-app创建工程模板
```
cnpm install -g create-react-app
create-react-app my-app
```
