<head>
	<link rel="stylesheet" type="text/css" href="connect4Style.css">
	<script src="SlotType.js"></script>
	<script src="Globals.js"></script>
	<script src="GlobalMethods.js"></script>
	<script src="NeuralNetworkMethods.js"></script>
	<script src="A_Star.js"></script>
	<script src="ComputerMoves.js"></script>
	<script src="GameControl.js"></script>
	<script>
		InitNeuralNetwork();
	</script>
</head>
<?php
	require_once("../../includes/header.php");
?>



<html>
	<body style="background-image: url('../pictures/Knex/Towers/100_1257.JPG')">
		<div class="container mainpanelcontainer" align="center">
			<div class="panel-group paneledit" style="background-color:white">
				<button onclick="ResetGame()">RESET</button>
				<table border="1">
					<tr>
						<td id="slot_0_0" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_0_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
					<tr>
						<td id="slot_1_0"   onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_1_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
					<tr>
						<td id="slot_2_0"   onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_2_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
					<tr>
						<td id="slot_3_0"   onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_3_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
					<tr>
						<td id="slot_4_0"   onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_4_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
					<tr>
						<td id="slot_5_0"   onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_1" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_2" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_3" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_4" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_5" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
						<td id="slot_5_6" onclick="PerformMainUserMove(this.id)" class="conn4GridSlot"></td>
					</tr>
				</table>
			</div>
		</div>
	</body>
</html>