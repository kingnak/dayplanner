import QtQuick 2.0
import QtQuick.Dialogs 1.2

MessageDialog {
	Component.onCompleted: open();

	title: "Day Planner"
	text: "Fehler beim Starten:\n" + messageForCode();
	standardButtons: MessageDialog.Ok
	onAccepted: Qt.quit(1);
	onRejected: Qt.quit(1);

	function messageForCode() {
		switch (dbErrorCode) {
			case 0: return "Kein Fehler";
			case 1: return "Datenbank Version ist zu neu";
			case 2: return "Datenbank Version ist zu alt";
			case 3: return "Datenbank kann nicht geöffnet werden";
			case 4: return "Datenbank kann nicht erstellt werden";
			case 5: return "Unbekannter Fehler";
			default: return "Unbekannter Fehlercode: " + dbErrorCode;
		}
	}
}
