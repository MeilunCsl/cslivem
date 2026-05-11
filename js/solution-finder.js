/* ===================================================
   TOTEM SOLUTION FINDER v2.0
   简化版：输入国家 → 输出支持的支付方案
   API接口预留：数据可通过后端接口替换
   =================================================== */
var TotemSolutionFinder = (function () {
    'use strict';

    // ==================== 国家方案数据 (可通过API替换) ====================
    var SOLUTION_FINDER_DATA = [
        { code: 'CN', name: '中国', nameEn: 'China', flag: '🇨🇳',
          cash: '支持人民币纸币(¥1-¥100)与硬币收款',
          cashEn: 'Supports RMB bills (¥1-¥100) and coins',
          nonCash: '支持银联闪付NFC、支付宝/微信扫码、IC银行卡',
          nonCashEn: 'UnionPay NFC, Alipay/WeChat QR, IC bank card',
          devices: ['自动售货机','自助售票机','无人零售柜','自助终端','停车场','充电桩','自助洗衣'] },
        { code: 'US', name: '美国', nameEn: 'United States', flag: '🇺🇸',
          cash: '支持美元纸币($1-$100)与硬币，高容量钱箱',
          cashEn: 'USD bills ($1-$100) and coins, high-capacity cashbox',
          nonCash: 'Apple Pay/Google Pay NFC、信用卡/借记卡',
          nonCashEn: 'Apple Pay/Google Pay NFC, credit/debit card',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'EU', name: '欧洲', nameEn: 'Europe', flag: '🇪🇺',
          cash: '支持欧元(€5-€500)纸币与硬币',
          cashEn: 'Euro bills (€5-€500) and coins',
          nonCash: 'Visa/Mastercard NFC、EMV芯片卡、移动支付',
          nonCashEn: 'Visa/Mastercard NFC, EMV chip card, mobile payment',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售','自助终端'] },
        { code: 'UK', name: '英国', nameEn: 'United Kingdom', flag: '🇬🇧',
          cash: '支持英镑(£5-£50)纸币与硬币',
          cashEn: 'Sterling bills (£5-£50) and coins',
          nonCash: 'Contactless NFC、Apple Pay、IC卡',
          nonCashEn: 'Contactless NFC, Apple Pay, IC card',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'JP', name: '日本', nameEn: 'Japan', flag: '🇯🇵',
          cash: '支持日元(¥1000-¥10000)纸币与硬币',
          cashEn: 'Yen bills (¥1000-¥10000) and coins',
          nonCash: 'Suica/Pasmo交通IC卡、NFC支付',
          nonCashEn: 'Suica/Pasmo transit IC cards, NFC payment',
          devices: ['自动售货机','自助售票机','自助洗衣','自助终端','充电桩','无人零售'] },
        { code: 'KR', name: '韩国', nameEn: 'South Korea', flag: '🇰🇷',
          cash: '支持韩元(₩1000-₩50000)纸币与硬币',
          cashEn: 'Won bills (₩1000-₩50000) and coins',
          nonCash: 'T-money交通卡、Samsung Pay NFC、信用卡',
          nonCashEn: 'T-money transit card, Samsung Pay NFC, credit card',
          devices: ['自动售货机','自助售票机','自助洗衣','自助终端','充电桩','无人零售'] },
        { code: 'AU', name: '澳大利亚', nameEn: 'Australia', flag: '🇦🇺',
          cash: '支持澳元($5-$100)纸币与硬币',
          cashEn: 'AUD bills ($5-$100) and coins',
          nonCash: 'Visa/Mastercard NFC、EMV刷卡',
          nonCashEn: 'Visa/Mastercard NFC, EMV card payment',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'IN', name: '印度', nameEn: 'India', flag: '🇮🇳',
          cash: '支持印度卢比(₹10-₹2000)纸币与硬币',
          cashEn: 'Indian Rupee bills (₹10-₹2000) and coins',
          nonCash: 'UPI扫码、RuPay NFC、Paytm等移动支付',
          nonCashEn: 'UPI QR, RuPay NFC, Paytm mobile payment',
          devices: ['自动售货机','自助售票机','无人零售','自助终端','充电桩'] },
        { code: 'BR', name: '巴西', nameEn: 'Brazil', flag: '🇧🇷',
          cash: '支持巴西雷亚尔(R$2-R$200)纸币与硬币',
          cashEn: 'Brazilian Real bills (R$2-R$200) and coins',
          nonCash: 'Pix扫码、NFC银行卡、信用卡',
          nonCashEn: 'Pix QR, NFC bank card, credit card',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'RU', name: '俄罗斯', nameEn: 'Russia', flag: '🇷🇺',
          cash: '支持卢布(₽50-₽5000)纸币与硬币',
          cashEn: 'Ruble bills (₽50-₽5000) and coins',
          nonCash: 'Mir卡NFC、SBP扫码支付',
          nonCashEn: 'Mir card NFC, SBP QR payment',
          devices: ['自动售货机','自助售票机','自助洗衣','自助终端','充电桩','无人零售'] },
        { code: 'AE', name: '阿联酋', nameEn: 'UAE', flag: '🇦🇪',
          cash: '支持迪拉姆(AED5-AED1000)纸币与硬币',
          cashEn: 'Dirham bills (AED5-AED1000) and coins',
          nonCash: 'Apple Pay/Samsung Pay NFC、Visa/Mastercard',
          nonCashEn: 'Apple Pay/Samsung Pay NFC, Visa/Mastercard',
          devices: ['自动售货机','自助售票机','停车场','充电桩','无人零售','自助终端'] },
        { code: 'SA', name: '沙特阿拉伯', nameEn: 'Saudi Arabia', flag: '🇸🇦',
          cash: '支持沙特里亚尔(SAR5-SAR500)纸币与硬币',
          cashEn: 'Saudi Riyal bills (SAR5-SAR500) and coins',
          nonCash: 'mada卡NFC、Apple Pay、STC Pay',
          nonCashEn: 'mada card NFC, Apple Pay, STC Pay',
          devices: ['自动售货机','自助售票机','停车场','充电桩','无人零售'] },
        { code: 'TH', name: '泰国', nameEn: 'Thailand', flag: '🇹🇭',
          cash: '支持泰铢(฿20-฿1000)纸币与硬币',
          cashEn: 'Thai Baht bills (฿20-฿1000) and coins',
          nonCash: 'PromptPay扫码、NFC银行卡',
          nonCashEn: 'PromptPay QR, NFC bank card',
          devices: ['自动售货机','自助售票机','自助洗衣','自助终端','充电桩','无人零售'] },
        { code: 'VN', name: '越南', nameEn: 'Vietnam', flag: '🇻🇳',
          cash: '支持越南盾(₫10000-₫500000)纸币与硬币',
          cashEn: 'Vietnamese Dong bills (₫10000-₫500000) and coins',
          nonCash: 'VNPay/MoMo扫码、NFC银行卡',
          nonCashEn: 'VNPay/MoMo QR, NFC bank card',
          devices: ['自动售货机','自助售票机','自助洗衣','自助终端','无人零售'] },
        { code: 'ID', name: '印度尼西亚', nameEn: 'Indonesia', flag: '🇮🇩',
          cash: '支持印尼盾(Rp2000-Rp100000)纸币与硬币',
          cashEn: 'Indonesian Rupiah bills (Rp2000-Rp100000) and coins',
          nonCash: 'GoPay/OVO扫码、NFC银行卡',
          nonCashEn: 'GoPay/OVO QR, NFC bank card',
          devices: ['自动售货机','自助售票机','自助洗衣','无人零售','自助终端'] },
        { code: 'MY', name: '马来西亚', nameEn: 'Malaysia', flag: '🇲🇾',
          cash: '支持林吉特(RM1-RM100)纸币与硬币',
          cashEn: 'Ringgit bills (RM1-RM100) and coins',
          nonCash: "Touch 'n Go NFC、GrabPay扫码、Visa/Mastercard",
          nonCashEn: "Touch 'n Go NFC, GrabPay QR, Visa/Mastercard",
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售','自助终端'] },
        { code: 'PH', name: '菲律宾', nameEn: 'Philippines', flag: '🇵🇭',
          cash: '支持菲律宾比索(₱20-₱1000)纸币与硬币',
          cashEn: 'Philippine Peso bills (₱20-₱1000) and coins',
          nonCash: 'GCash/GrabPay扫码支付',
          nonCashEn: 'GCash/GrabPay QR payment',
          devices: ['自动售货机','自助售票机','自助洗衣','无人零售'] },
        { code: 'SG', name: '新加坡', nameEn: 'Singapore', flag: '🇸🇬',
          cash: '支持新加坡元(S$2-S$100)纸币与硬币',
          cashEn: 'SGD bills (S$2-S$100) and coins',
          nonCash: 'EZ-Link/NETS NFC、GrabPay、Visa/Mastercard',
          nonCashEn: 'EZ-Link/NETS NFC, GrabPay, Visa/Mastercard',
          devices: ['自动售货机','自助售票机','自助洗衣','充电桩','无人零售','自助终端','停车场'] },
        { code: 'MX', name: '墨西哥', nameEn: 'Mexico', flag: '🇲🇽',
          cash: '支持墨西哥比索($20-$1000)纸币与硬币',
          cashEn: 'Mexican Peso bills ($20-$1000) and coins',
          nonCash: 'CoDi扫码、NFC银行卡',
          nonCashEn: 'CoDi QR, NFC bank card',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'ZA', name: '南非', nameEn: 'South Africa', flag: '🇿🇦',
          cash: '支持南非兰特(R10-R200)纸币与硬币',
          cashEn: 'South African Rand bills (R10-R200) and coins',
          nonCash: 'SnapScan/Zapper扫码、NFC银行卡',
          nonCashEn: 'SnapScan/Zapper QR, NFC bank card',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'TR', name: '土耳其', nameEn: 'Turkey', flag: '🇹🇷',
          cash: '支持土耳其里拉(₺5-₺200)纸币与硬币',
          cashEn: 'Turkish Lira bills (₺5-₺200) and coins',
          nonCash: 'Troy NFC、QR扫码支付',
          nonCashEn: 'Troy NFC, QR payment',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] },
        { code: 'DE', name: '德国', nameEn: 'Germany', flag: '🇩🇪',
          cash: '支持欧元纸币与硬币，德国现金使用率较高',
          cashEn: 'Euro bills and coins, high cash usage in Germany',
          nonCash: 'Girocard NFC、Apple Pay、Visa/Mastercard',
          nonCashEn: 'Girocard NFC, Apple Pay, Visa/Mastercard',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售','自助终端'] },
        { code: 'FR', name: '法国', nameEn: 'France', flag: '🇫🇷',
          cash: '支持欧元纸币与硬币',
          cashEn: 'Euro bills and coins',
          nonCash: 'CB卡NFC、Apple Pay、Visa/Mastercard',
          nonCashEn: 'CB card NFC, Apple Pay, Visa/Mastercard',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售','自助终端'] },
        { code: 'CA', name: '加拿大', nameEn: 'Canada', flag: '🇨🇦',
          cash: '支持加元($5-$100)纸币与硬币',
          cashEn: 'CAD bills ($5-$100) and coins',
          nonCash: 'Interac NFC、Apple Pay、Visa/Mastercard',
          nonCashEn: 'Interac NFC, Apple Pay, Visa/Mastercard',
          devices: ['自动售货机','自助售票机','自助洗衣','停车场','充电桩','无人零售'] }
    ];

    // ==================== API 接口层 (预留) ====================
    var API = {
        getSolutionFinderData: function () {
            // 未来替换为: fetch('/api/solution-finder')
            return Promise.resolve(SOLUTION_FINDER_DATA);
        },
        searchByCountry: function (countryCode) {
            // 未来替换为: fetch('/api/solution-finder/' + code)
            var result = SOLUTION_FINDER_DATA.find(function (c) { return c.code === countryCode; });
            return Promise.resolve(result || null);
        }
    };

    // ==================== 工具函数 ====================
    function getLang() {
        return (typeof TotemSite !== 'undefined' && TotemSite.getCurrentLang) ? TotemSite.getCurrentLang() : (localStorage.getItem('lang') || 'zh');
    }
    function isEn() { return getLang() === 'en'; }

    // ==================== 匹配国家 ====================
    function matchCountry(keyword) {
        keyword = keyword.toLowerCase().trim();
        if (!keyword) return null;
        return SOLUTION_FINDER_DATA.find(function (c) {
            return c.name === keyword ||
                   c.nameEn.toLowerCase() === keyword ||
                   c.code.toLowerCase() === keyword ||
                   c.name.toLowerCase().indexOf(keyword) !== -1 ||
                   c.nameEn.toLowerCase().indexOf(keyword) !== -1;
        });
    }

    // ==================== 初始化 ====================
    function initFinder() {
        var form = document.getElementById('solutionFinderForm');
        var input = document.getElementById('finderCountryInput');
        var resultContainer = document.getElementById('finderResults');
        if (!form || !input) return;

        if (form.dataset.finderInit === 'true') return;
        form.dataset.finderInit = 'true';

        // 表单提交（回车或点击按钮）
        form.addEventListener('submit', function (e) {
            e.preventDefault();
            var country = matchCountry(input.value);
            if (country) {
                input.value = isEn() ? country.nameEn : country.name;
                input.setAttribute('data-code', country.code);
                renderResults(country, resultContainer);
            } else if (resultContainer) {
                var en = isEn();
                resultContainer.innerHTML = '<div class="finder-empty">' +
                    '<i class="fas fa-exclamation-circle"></i>' +
                    '<p>' + (en ? 'Country not found. Try: China, US, Japan...' : '未找到该国家，请尝试输入：中国、美国、日本…') + '</p></div>';
                resultContainer.style.display = 'block';
            }
        });
    }

    // ==================== 渲染简洁结果 ====================
    function renderResults(country, container) {
        if (!container) return;
        var en = isEn();

        var html = '<div class="finder-simple-result">';

        // 国家标题
        html += '<div class="finder-simple-header">';
        html += '<span class="finder-flag">' + country.flag + '</span>';
        html += '<h3>' + (en ? country.nameEn : country.name) + '</h3>';
        html += '</div>';

        // 方案列表
        html += '<div class="finder-simple-rows">';

        // 现金方案
        html += '<div class="finder-simple-row">';
        html += '<span class="finder-row-icon finder-row-cash"><i class="fas fa-money-bill-wave"></i></span>';
        html += '<span class="finder-row-label">' + (en ? 'Cash' : '现金方案') + '</span>';
        html += '<span class="finder-row-desc">' + (en ? country.cashEn : country.cash) + '</span>';
        html += '</div>';

        // 非现金方案
        html += '<div class="finder-simple-row">';
        html += '<span class="finder-row-icon finder-row-noncash"><i class="fas fa-credit-card"></i></span>';
        html += '<span class="finder-row-label">' + (en ? 'Cashless' : '非现金方案') + '</span>';
        html += '<span class="finder-row-desc">' + (en ? country.nonCashEn : country.nonCash) + '</span>';
        html += '</div>';

        html += '</div>';

        // 适用设备
        if (country.devices && country.devices.length > 0) {
            html += '<div class="finder-simple-devices">';
            html += '<span class="finder-devices-label"><i class="fas fa-cubes"></i> ' + (en ? 'Devices' : '适用设备') + '：</span>';
            html += '<span class="finder-devices-list">' + country.devices.join(' / ') + '</span>';
            html += '</div>';
        }

        // CTA
        html += '<div class="finder-simple-cta">';
        html += '<a href="/contact" class="btn-primary btn-sm">' + (en ? 'Contact Sales' : '联系销售获取详情') + ' <i class="fas fa-arrow-right"></i></a>';
        html += '</div>';

        html += '</div>';

        container.innerHTML = html;
        container.style.display = 'block';

        // 滚动到搜索模块顶部（而非结果区域），避免搜索框被遮挡
        setTimeout(function () {
            var finderSection = document.getElementById('solutionFinder');
            if (finderSection) {
                var offset = finderSection.getBoundingClientRect().top + window.pageYOffset - 80;
                window.scrollTo({ top: offset, behavior: 'smooth' });
            }
        }, 100);
    }

    // ==================== 语言切换刷新 ====================
    function refreshOnLangChange() {
        var input = document.getElementById('finderCountryInput');
        var resultContainer = document.getElementById('finderResults');
        if (!input || !resultContainer) return;

        var code = input.getAttribute('data-code');
        if (code) {
            var country = SOLUTION_FINDER_DATA.find(function (c) { return c.code === code; });
            if (country) {
                input.value = isEn() ? country.nameEn : country.name;
                renderResults(country, resultContainer);
            }
        }
    }

    // ==================== 初始化 ====================
    function init() { initFinder(); }

    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', init);
    } else {
        init();
    }

    // ==================== 公开接口 ====================
    return {
        API: API,
        SOLUTION_FINDER_DATA: SOLUTION_FINDER_DATA,
        initFinder: initFinder,
        refreshOnLangChange: refreshOnLangChange
    };
})();
