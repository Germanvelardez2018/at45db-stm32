#Driver for AT45DB041 based in STM32 HAL

Controller for flash memory AT45DB041. Based on the STM32 HAL project but the code is easy to modify and use on another platform.



 <h4 align="center">Component Connection</h4>
 <div align="center" >
<img  src="img/connections.jpg" border="1px" 
     height="480px" width="560px"/>
</div>

<h4 align="center">Signal from logic analyzer
</h4>
<p> Command 0xD7 is sent to obtain the 2 status registers: |0x9D | 0x88|</p>
 <div align="center" >
<img  src="img/signals.jpg" border="1px" 
     height="480px" width="560px"/>
</div>



<h4 align="center">Signal from logic analyzer
</h4>
<p> Command 0x9F is sent to obtain the 4 ID registers: |0x1F|0x24|0x00|0x01|</p>
 <div align="center" >
<img  src="img/get_id.jpg" border="1px" 
     height="480px" width="560px"/>
</div>




<h4 align="center">Signal from logic analyzer
</h4>
<p> Write buffer1 (0x84) with data = "Boca jr murio en madrid \n"|</p>
 <div align="center" >
<img  src="img/writebuffer1.jpg" border="1px" 
     height="480px" width="560px"/>
</div>





<h4 align="center">Signal from logic analyzer
</h4>
<p> Read buffer1 with command: 0xD4 </p>
 <div align="center" >
<img  src="img/readbuffer1.jpg" border="1px" 
     height="480px" width="560px"/>
</div>
