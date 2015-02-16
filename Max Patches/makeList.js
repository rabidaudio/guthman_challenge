inlets = 1;
outlets = 1;

var x = "";


function msg_int(r) {
	if(r == 13) {
		x = x.slice(1);
		outlet(0, x);
		x = "";
	}
	else {
		s = String.fromCharCode(r);
		x = x + s;
	}
}