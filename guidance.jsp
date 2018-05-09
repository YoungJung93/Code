<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<% request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=EUC-KR">
<title> M A P </title>
</head>
<body>
<center><h3>M A P</h3></center>
<hr>
<script>
	var canvas,context;
	var exitImage = new Image();
	var flameSensor = new Image();
	window.addEventListener("load",InitEvent,false);
	exitImage.src = "exit.png";
	flameSensor.src = "flameSensor.JPG";
	exitImage.addEventListener("load",drawExit,false);
	flameSensor.addEventListener("load",drawSensor,false);

	function InitEvent() {
		canvas=document.getElementById("square");
		context=canvas.getContext("2d");
		
	 	context.fillstyle="black";
		context.fillRect(0,0,400,400); // 맵 전체 크기

		context.clearRect(100,0,50,400); // 길
		context.clearRect(250,0,50,400); // 길
		context.clearRect(0,100,400,50); // 길
		context.clearRect(0,250,400,50); // 길
		
		context.fillRect(120,100,3,3); // 현재 위치
	}
	function drawExit() { // 비상구 그림
		context.drawImage(exitImage,405,110,50,30);
	}
	function drawSensor() { // 불꽃 센서 그림
		context.drawImage(flameSensor,180,80,40,20);
		context.drawImage(flameSensor,180,230,40,20);
		context.drawImage(flameSensor,60,190,40,20);
		context.drawImage(flameSensor,300,190,40,20);
	}
</script>
	<center><canvas id="square" width="500" height="500"></canvas></center>
	<%=request.getServerPort()  %>
	<%
		String val=request.getParameter("value");
	%>
	<%=val %>
	<a href=/exitGuidance/server.jsp?value=<%=val%>>고고</a>
</body>
</html>
<script language='javascript'>
   window.setTimeout('window.location.reload()',2000); //1초마다 리플리쉬 시킨다 1000이 1초가 된다.
 </script>