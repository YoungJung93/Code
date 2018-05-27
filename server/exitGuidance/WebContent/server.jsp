<%@ page language="java" contentType="text/html; charset=EUC-KR"
    pageEncoding="EUC-KR"%>
<%=request.getParameter("value")%>
<script language='javascript'>
   window.setTimeout('window.location.reload()',2000); //1초마다 리플리쉬 시킨다 1000이 1초가 된다.
 </script>