var seetaface = require('seetaface/build/Release/seetaface');
var cv = require('opencv');


cv.readImage("./mona.png", function(err, mat){
  if(mat.channels() >= 3){
    mat.convertGrayscale();
  }
  
  var data = mat.getData();
  console.log(mat.width(),mat.height(),mat.channels());
  console.log(data.length);
    seetaface.detect(data,mat.width(),mat.height(),function(msg){
      console.log(msg); // 'hello world'
    });
})