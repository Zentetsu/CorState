"use strict";
var __create = Object.create;
var __defProp = Object.defineProperty;
var __getOwnPropDesc = Object.getOwnPropertyDescriptor;
var __getOwnPropNames = Object.getOwnPropertyNames;
var __getProtoOf = Object.getPrototypeOf;
var __hasOwnProp = Object.prototype.hasOwnProperty;
var __export = (target, all) => {
  for (var name in all)
    __defProp(target, name, { get: all[name], enumerable: true });
};
var __copyProps = (to, from, except, desc) => {
  if (from && typeof from === "object" || typeof from === "function") {
    for (let key of __getOwnPropNames(from))
      if (!__hasOwnProp.call(to, key) && key !== except)
        __defProp(to, key, { get: () => from[key], enumerable: !(desc = __getOwnPropDesc(from, key)) || desc.enumerable });
  }
  return to;
};
var __toESM = (mod, isNodeMode, target) => (target = mod != null ? __create(__getProtoOf(mod)) : {}, __copyProps(
  // If the importer is in node compatibility mode or this is not an ESM
  // file that has been converted to a CommonJS file using a Babel-
  // compatible transform (i.e. "__esModule" has not been set), then set
  // "default" to the CommonJS "module.exports" for node compatibility.
  isNodeMode || !mod || !mod.__esModule ? __defProp(target, "default", { value: mod, enumerable: true }) : target,
  mod
));
var __toCommonJS = (mod) => __copyProps(__defProp({}, "__esModule", { value: true }), mod);

// src/extension.ts
var extension_exports = {};
__export(extension_exports, {
  activate: () => activate,
  deactivate: () => deactivate
});
module.exports = __toCommonJS(extension_exports);
var vscode = __toESM(require("vscode"));
var fs = __toESM(require("fs"));
function activate(context) {
  const openDesigner = vscode.commands.registerCommand("corstate.open", async () => {
    const panel = createWebviewPanel(context);
    const choice = await vscode.window.showQuickPick(
      ["New State Machine", "Load from JSON"],
      { placeHolder: "How do you want to start?" }
    );
    if (choice === "Load from JSON") {
      const uri = await vscode.window.showOpenDialog({
        filters: { "JSON": ["json"] },
        canSelectMany: false
      });
      if (uri && uri[0]) {
        const raw = fs.readFileSync(uri[0].fsPath, "utf8");
        const json = JSON.parse(raw);
        panel.webview.postMessage({ command: "load", data: json });
      }
    } else {
      panel.webview.postMessage({ command: "new" });
    }
    panel.webview.onDidReceiveMessage(async (message) => {
      if (message.command === "save") {
        const uri = await vscode.window.showSaveDialog({
          filters: { "JSON": ["json"] },
          defaultUri: vscode.Uri.file("StateMachine.json")
        });
        if (uri) {
          fs.writeFileSync(uri.fsPath, JSON.stringify(message.data, null, 4));
          vscode.window.showInformationMessage("State machine saved.");
        }
      }
    }, void 0, context.subscriptions);
  });
  context.subscriptions.push(openDesigner);
}
function createWebviewPanel(context) {
  const panel = vscode.window.createWebviewPanel(
    "corstate",
    "CorState",
    vscode.ViewColumn.One,
    {
      enableScripts: true,
      localResourceRoots: [
        vscode.Uri.joinPath(context.extensionUri, "media")
      ],
      retainContextWhenHidden: true
      // Keep canvas state when tab is hidden
    }
  );
  panel.webview.html = getWebviewContent(panel.webview, context.extensionUri);
  return panel;
}
function getWebviewContent(webview, extensionUri) {
  const mediaUri = (file) => webview.asWebviewUri(vscode.Uri.joinPath(extensionUri, "media", file));
  return `<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="Content-Security-Policy" content="
        default-src 'none';
        script-src ${webview.cspSource} 'unsafe-inline' 'unsafe-eval';
        style-src ${webview.cspSource} 'unsafe-inline';
    ">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>CorState</title>
    <link rel="stylesheet" href="${mediaUri("app.css")}">
</head>
<body>
    <div id="toolbar">
        <button id="btn-add-state">Add State</button>
        <button id="btn-add-transition">Add Transition</button>
        <button id="btn-save">Save</button>
        <span id="breadcrumb"></span>
    </div>
    <div id="canvas-container"></div>

    <script src="${mediaUri("joint.min.js")}"></script>
    <script src="${mediaUri("app.js")}"></script>
</body>
</html>`;
}
function deactivate() {
}
// Annotate the CommonJS export names for ESM import in node:
0 && (module.exports = {
  activate,
  deactivate
});
//# sourceMappingURL=extension.js.map
