# Totem Hardware Solutions 官网

## 项目简介

Totem Hardware Solutions 企业产品展示型静态网站，面向全球自助设备运营商，展示现金与非现金支付硬件解决方案。

## 技术栈

- **HTML5** + **CSS3** + **Vanilla JavaScript**
- 无框架依赖，纯静态部署
- 外部 CDN：Font Awesome 6（图标）、Google Fonts（Inter + Plus Jakarta Sans）

## 核心模块

| 文件 | 说明 |
|------|------|
| `js/app.js` | 全部业务逻辑：产品数据、解决方案数据、i18n 中英文切换、搜索过滤器、页面动态渲染、滚动动画等 |
| `js/solution-finder.js` | 首页方案搜索器（国家-支付方式-设备类型匹配） |
| `css/style.css` | 全站统一样式，包含响应式断点（950px / 600px） |

## 页面结构

### 首页
- `index.html` — 方案搜索器、产品卡片、行业应用入口、优势介绍

### 产品中心
- `products.html` — 产品总览
- `product-reader.html` — 读卡器系列
- `product-banknote.html` — 纸币器系列
- `product-coin.html` — 硬币器系列
- `product-scanner.html` — 扫码器系列
- `product-nfc.html` — 非接读卡器

### 子产品详情
- `product-reader-vpos-touch.html` — VPOS TOUCH
- `product-reader-onyx.html` — ONYX
- `product-reader-vpos-media4.html` — VPOS Media 4
- `product-reader-vpos-media4-mini.html` — VPOS Media 4 Mini

### 解决方案
- `solutions.html` — 方案总览
- `solution-vending.html` — 自动售货机
- `solution-charging.html` — 充电桩支付
- `solution-ticket.html` — 自助售票机
- `solution-laundry.html` — 自助洗衣房
- `solution-retail.html` — 无人零售柜

### 其他页面
- `about.html` — 公司介绍
- `contact.html` — 联系我们
- `support.html` — 技术支持
- `developers.html` — 开发者资源
- `industries.html` — 行业应用

## 数据特征

- 所有产品和解决方案数据以 JavaScript 对象形式存储在 `js/app.js` 中，支持中英文双语字段（`title` / `titleEn`、`desc` / `descEn`）
- 搜索功能基于硬编码的国家-支付方式-设备类型支持矩阵，不依赖后端接口
- 图片当前使用 Font Awesome 图标占位，后续可替换为真实产品图片

## 本地运行

```bash
# 使用 Node.js 启动本地服务器
npx serve .

# 或使用 Python
python -m http.server 3000
```

然后在浏览器中打开 `http://localhost:3000`。

## 当前维护状态

- [ ] 表单提交仅打印到控制台，未连接后端 API
- [ ] 部分静态文案尚未全部国际化
- [ ] 首页设备展示区域为占位图，待替换真实产品图片
- [ ] 场景卡片（适用场景区域）待替换为真实场景图片

## 许可

本项目仅供内部使用。
