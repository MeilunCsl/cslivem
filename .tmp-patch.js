const fs = require("fs");
const p = require("path");
const b = p.join("C:","Users","Administrator","Desktop",String.fromCharCode(0x65B0,0x5EFA,0x6587,0x4EF6,0x5939),"TotemPage","totem-site");
const ap = p.join(b,"js","app.js");
const src = fs.readFileSync(ap, "utf8");
const lines = src.split("\n");

// Find initSearchOnHome start (line 1180, 0-indexed 1179)
let startIdx = -1;
for (let i = 0; i < lines.length; i++) {
  if (lines[i].indexOf("function initSearchOnHome") !== -1) {
    startIdx = i - 1; // include comment line above
    break;
  }
}
console.log("initSearchOnHome starts at line:", startIdx + 1);

// Find end of function (the closing brace at same indent level)
let braceCount = 0;
let endIdx = -1;
for (let i = startIdx; i < lines.length; i++) {
  const line = lines[i];
  for (let j = 0; j < line.length; j++) {
    if (line[j] === "{") braceCount++;
    if (line[j] === "}") braceCount--;
  }
  if (braceCount === 0 && i > startIdx) {
    endIdx = i;
    break;
  }
}
console.log("initSearchOnHome ends at line:", endIdx + 1);

// Also find performSearch and renderSearchResults
let psStart = -1, psEnd = -1;
for (let i = 0; i < lines.length; i++) {
  if (lines[i].indexOf("function performSearch(") !== -1) { psStart = i; break; }
}
console.log("performSearch starts at line:", psStart + 1);
braceCount = 0;
for (let i = psStart; i < lines.length; i++) {
  for (let j = 0; j < lines[i].length; j++) {
    if (lines[i][j] === "{") braceCount++;
    if (lines[i][j] === "}") braceCount--;
  }
  if (braceCount === 0 && i > psStart) { psEnd = i; break; }
}
console.log("performSearch ends at line:", psEnd + 1);

// Check if renderRegionSearchResults already exists
const hasRegion = src.indexOf("renderRegionSearchResults") !== -1;
console.log("Has region search already:", hasRegion);

// Read existing renderSearchResults for reference
let rsStart = -1, rsEnd = -1;
for (let i = 0; i < lines.length; i++) {
  if (lines[i].indexOf("function renderSearchResults(") !== -1) { rsStart = i; break; }
}
console.log("renderSearchResults starts at line:", rsStart + 1);

console.log("Total lines:", lines.length);
