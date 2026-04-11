/*
 * File: extension.ts
 * Project: CorState
 * License: GPLv3
 */

import * as vscode from 'vscode';
import * as fs from 'fs';
import * as path from 'path';

export function activate(context: vscode.ExtensionContext) {

    // Command: Open CorState designer
    const openDesigner = vscode.commands.registerCommand('corstate.open', async () => {
        const panel = createWebviewPanel(context);

        // Prompt user: new or load existing
        const choice = await vscode.window.showQuickPick(
            ['New State Machine', 'Load from JSON'],
            { placeHolder: 'How do you want to start?' }
        );

        if (choice === 'Load from JSON') {
            const uri = await vscode.window.showOpenDialog({
                filters: { 'JSON': ['json'] },
                canSelectMany: false
            });

            if (uri && uri[0]) {
                const raw = fs.readFileSync(uri[0].fsPath, 'utf8');
                const json = JSON.parse(raw);
                panel.webview.postMessage({ command: 'load', data: json });
            }
        } else {
            panel.webview.postMessage({ command: 'new' });
        }

        // Handle save request from webview
        panel.webview.onDidReceiveMessage(async (message) => {
            if (message.command === 'save') {
                const uri = await vscode.window.showSaveDialog({
                    filters: { 'JSON': ['json'] },
                    defaultUri: vscode.Uri.file('StateMachine.json')
                });

                if (uri) {
                    fs.writeFileSync(uri.fsPath, JSON.stringify(message.data, null, 4));
                    vscode.window.showInformationMessage('State machine saved.');
                }
            }
        }, undefined, context.subscriptions);
    });

    context.subscriptions.push(openDesigner);
}

function createWebviewPanel(context: vscode.ExtensionContext): vscode.WebviewPanel {
    const panel = vscode.window.createWebviewPanel(
        'corstate',
        'CorState',
        vscode.ViewColumn.One,
        {
            enableScripts: true,
            localResourceRoots: [
                vscode.Uri.joinPath(context.extensionUri, 'media')
            ],
            retainContextWhenHidden: true  // Keep canvas state when tab is hidden
        }
    );

    panel.webview.html = getWebviewContent(panel.webview, context.extensionUri);

    return panel;
}

function getWebviewContent(webview: vscode.Webview, extensionUri: vscode.Uri): string {
    const mediaUri = (file: string) =>
        webview.asWebviewUri(vscode.Uri.joinPath(extensionUri, 'media', file));

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
    <link rel="stylesheet" href="${mediaUri('app.css')}">
</head>
<body>
    <div id="toolbar">
        <button id="btn-add-state">Add State</button>
        <button id="btn-add-transition">Add Transition</button>
        <button id="btn-save">Save</button>
        <span id="breadcrumb"></span>
    </div>
    <div id="canvas-container"></div>

    <script src="${mediaUri('joint.min.js')}"></script>
    <script src="${mediaUri('app.js')}"></script>
</body>
</html>`;
}

export function deactivate() {}