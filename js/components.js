/**
 * Totem 公共组件模板
 * 导航栏 + 页脚，所有页面引入此文件即可自动注入
 * 修改导航栏/页脚只需改这一个文件
 */

document.addEventListener('DOMContentLoaded', function () {
    // ===== 注入导航栏 =====
    var nav = document.createElement('nav');
    nav.className = 'navbar';
    nav.innerHTML = `
    <div class="container nav-container">
        <a href="/" class="logo" id="totemLogo">Totem<span>.</span></a>
        <div class="hamburger" id="hamburger"><i class="fas fa-bars"></i></div>
        <div class="nav-links" id="navLinks">
            <div class="nav-item has-dropdown">
                <a href="/products" style="color:var(--primary);">产品中心 <i class="fas fa-chevron-down"></i></a>
                <div class="dropdown">
                    <a href="/products/reader">读卡器系列</a>
                    <a href="/products/banknote">纸币器系列</a>
                    <a href="/products/coin">硬币器系列</a>
                    <a href="/products/scanner">扫码器系列</a>
                    <a href="/products/nfc">非接读卡器</a>
                </div>
            </div>
            <div class="nav-item has-dropdown">
                <a href="/solutions">解决方案 <i class="fas fa-chevron-down"></i></a>
                <div class="dropdown">
                    <a href="/solutions/vending">自动售货机</a>
                    <a href="/solutions/charging">充电桩支付</a>
                    <a href="/solutions/ticket">自助售票机</a>
                    <a href="/solutions/laundry">自助洗衣房</a>
                    <a href="/solutions/retail">无人零售柜</a>
                </div>
            </div>
            <div class="nav-item"><a href="/industries">行业应用</a></div>
            <div class="nav-item"><a href="/support">技术支持</a></div>
            <div class="nav-item"><a href="/about">关于Totem</a></div>
        </div>
        <div class="nav-buttons">
            <div class="lang-switch" id="langSwitch"><i class="fas fa-globe"></i> <span id="currentLang">中文</span></div>
            <a href="/contact" class="demo-btn">获取报价</a>
        </div>
    </div>`;

    // 插入到 body 最前面
    document.body.insertBefore(nav, document.body.firstChild);

    // ===== 注入页脚 =====
    var footer = document.createElement('footer');
    footer.innerHTML = `
    <div class="container">
        <div class="footer-grid">
            <div class="footer-col">
                <h4>产品系列</h4>
                <ul>
                    <li><a href="/products/reader">读卡器</a></li>
                    <li><a href="/products/banknote">纸币接收器</a></li>
                    <li><a href="/products/coin">硬币器/找零器</a></li>
                </ul>
            </div>
            <div class="footer-col">
                <h4>解决方案</h4>
                <ul>
                    <li><a href="/solutions">自动售货机集成</a></li>
                    <li><a href="/solutions/charging">充电桩支付</a></li>
                </ul>
            </div>
            <div class="footer-col">
                <h4>技术支持</h4>
                <ul>
                    <li><a href="/support">驱动下载</a></li>
                    <li><a href="/developers">API文档</a></li>
                </ul>
            </div>
            <div class="footer-col">
                <h4>关于Totem</h4>
                <ul>
                    <li><a href="/about">公司简介</a></li>
                    <li><a href="/about">新闻动态</a></li>
                </ul>
                <div class="social-icons">
                    <i class="fab fa-linkedin-in"></i>
                    <i class="fab fa-twitter"></i>
                    <i class="fab fa-weixin"></i>
                </div>
            </div>
        </div>
        <div class="copyright">© 2026 Totem Hardware Solutions. 本页面仅供布局预览</div>
    </div>`;

    document.body.appendChild(footer);

    // ===== 导航栏滚动效果 =====
    window.addEventListener('scroll', function () {
        var navbar = document.querySelector('.navbar');
        if (navbar) {
            navbar.classList.toggle('scrolled', window.scrollY > 10);
        }
    });

    // ===== 移动端菜单 =====
    var hamburger = document.getElementById('hamburger');
    var navLinks = document.getElementById('navLinks');
    if (hamburger && navLinks) {
        hamburger.addEventListener('click', function () {
            navLinks.classList.toggle('active');
        });
        document.addEventListener('click', function (e) {
            if (window.innerWidth <= 950 && navLinks.classList.contains('active')
                && !navLinks.contains(e.target) && !hamburger.contains(e.target)) {
                navLinks.classList.remove('active');
            }
        });
    }

    // ===== 高亮当前页面导航 =====
    var currentPath = window.location.pathname;
    document.querySelectorAll('.nav-links a').forEach(function (link) {
        var href = link.getAttribute('href');
        if (href && href !== '/' && currentPath.startsWith(href)) {
            link.style.color = 'var(--primary)';
        }
    });
});
