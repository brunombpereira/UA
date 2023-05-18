// Image UpLoad Javascript
var file;

function updatePhoto(event) {
	var reader = new FileReader();
	reader.onload = function(event) {
		//Create an imagem
		var img = new Image();
		img.onload = function() {
			//Put imagen on screen
			const canvas = $("#photo")[0];
			const ctx = canvas.getContext("2d");
			ctx.drawImage(img,0,0,img.width,img.height,0,0,550, 450);
		}
		img.src = event.target.result;
	}

	file = event.target.files[0];
	//Obtain the file
	reader.readAsDataURL(file);
}

function uploadImage() {
    if(file != null) {
        sendFile(file);
        //Release the resources alocated to the selected image
        window.URL.revokeObjectURL(picURL);    
    }
    else alert("Missing image!");
}

function sendFile(file) {
	// Create a FormData object
	var formData = new FormData();
	formData.append("file", file);
	var xhr = new XMLHttpRequest();
	xhr.upload.addEventListener("progress", updateProgress, false);
	xhr.addEventListener("load", transferComplete, false);
	xhr.addEventListener("error", transferFailed, false);
	xhr.addEventListener("abort", transferCanceled, false);
	xhr.open("POST", "upload.php");
	xhr.send(formData);
}

function updateProgress(evt){
	if(evt.loaded == evt.total) alert("Okay");
}
