<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<% request.setCharacterEncoding("UTF-8"); %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
	<%
		String val=request.getParameter("value");
	%>
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
		context.fillRect(0,0,400,400); // �� ��ü ũ��

		context.clearRect(100,0,50,400); // ��
		context.clearRect(250,0,50,400); // ��
		context.clearRect(0,100,400,50); // ��
		context.clearRect(0,250,400,50); // ��
		
		context.fillRect(120,100,3,3); // ���� ��ġ
	}
	function drawExit() { // ��� �׸�
		context.drawImage(exitImage,405,110,50,30);
	}
	function drawSensor() { // �Ҳ� ���� �׸�
		context.drawImage(flameSensor,180,80,40,20);
		context.drawImage(flameSensor,180,230,40,20);
		context.drawImage(flameSensor,60,190,40,20);
		context.drawImage(flameSensor,300,190,40,20);
	}
</script>
	<center><canvas id="square" width="500" height="500"></canvas></center>
	<%=request.getServerPort()  %>
	
	<%=val %>
	<a href=/exitGuidance/server.jsp?value=<%=val%>>���</a>
</body>
</html>
<script language='javascript'>
   window.setTimeout('window.location.reload()',2000);
 </script>