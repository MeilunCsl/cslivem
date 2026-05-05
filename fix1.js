var fs = require("fs");
var c = fs.readFileSync("js/app.js", "utf8");
var lines = c.split("\n");
console.log("Start lines:", lines.length);

// Fix 1: Remove lines 2051-2058 (1-indexed) = index 2050-2057
// Confirm content
var expected = [
    "",
    "        // Page-specific rendering",
    "        var page = document.body.getAttribute('data-page');",
    "        if (page === 'product-detail') {",
    "            renderProductDetail(document.body.getAttribute('data-product'));",
    "        } else if (page === 'products-overview') {",
    "            renderProductsOverview();",
    "        }"
];
var ok = true;
for (var i = 0; i < 8; i++) {
    if (lines[2050 + i].trim() !== expected[i].trim()) {
        console.log("MISMATCH at index " + (2050 i) + ": got ['" + lines[2050+ i].trim() + "]");
        ok = false;
    }
}
if(!ok) { console.log("Content mismatch - aborting"); process.exit(1); }
console.log("Deleting lines 2051-2058");
lines.splice(2050, 8);
console.log("After fix1:", lines.length);
fs.writeFileSync("js/app.js", lines.join("\n"), "utf8");
console.log("Fix1 saved");