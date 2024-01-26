var peripheralBrowser;
var peripheralBrowserRef = serviceRegistry.findByName('io.macchina.btle.peripheralbrowser');
if (peripheralBrowserRef)
{
    peripheralBrowser = peripheralBrowserRef.instance();
}

var webEventNotifier;
var webEventNotifierRef = serviceRegistry.findByName('io.macchina.services.webeventnotifier');
if (webEventNotifierRef)
{
    webEventNotifier = webEventNotifierRef.instance();
}

var cancelTimer = null;

function startCancelTimer()
{
    stopCancelTimer();
    cancelTimer = setTimeout(() => { 
        console.log('Stopping scan after timeout...');
        peripheralBrowser.cancelBrowse(); 
    }, 20000);
}

function stopCancelTimer()
{
    if (cancelTimer != null)
    {
        clearTimeout(cancelTimer);
        cancelTimer = null;
    }
}

if (peripheralBrowser && webEventNotifier)
{
    peripheralBrowser.on('browseStarted', () => {
        webEventNotifier.notify('btle.scan.started', '');
    });

    peripheralBrowser.on('peripheralFound', ev => {
       webEventNotifier.notify('btle.scan.peripheralFound', JSON.stringify(ev.data));
    });
    
    peripheralBrowser.on('browseComplete', ev => {
        webEventNotifier.notify('btle.scan.completed', '');
        stopCancelTimer();
    });
    
    peripheralBrowser.on('browseError', ev => {
        console.error('browseError: %s', ev.data);
        webEventNotifier.notify('btle.scan.error', ev.data);
        stopCancelTimer();
    });

    webEventNotifier.on('event', ev => {
        if (ev.data.subjectName === 'btle.scan.command')
        {
            if (ev.data.data === 'start')
            {
                console.log('Starting scan...');
                if (peripheralBrowser.browseInProgress())
                {
                    peripheralBrowser.cancelBrowse();
                    system.sleep(200);
                }
                peripheralBrowser.browse(true);
                startCancelTimer();
            }
            else if (ev.data.data === 'stop')
            {
                console.log('Stopping scan...');
                peripheralBrowser.cancelBrowse();
                stopCancelTimer();
            }
        }
    });
	webEventNotifier.setEventSubjectNameFilter(webEventNotifier.$sub, 'btle.scan.command');
}
