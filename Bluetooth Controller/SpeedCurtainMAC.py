import asyncio
from bleak import BleakClient

ADDRESS = "9A966224-F6D6-94AB-E5A8-85849E49F597"

TEXT_CHARACTERISTIC = "9AFF"
COLOUR_CHARACTERISTIC = "7CFF"
FONT_CHARACTERISTIC = "2FFF"
STATUS_CHARACTERISTIC = "8BFF"
LENGTH_CHARACTERISTIC = "5EFF"
GO_CHARACTERISTIC = "6DFF"

RESET_CHARACTERISTIC = "6BFF"
INVERT_CHARACTERISTIC = "1CFF"
AUTOSCROLL_CHARACTERISTIC = "5CFF"
RIBBON_CHARACTERISTIC = "4CFF"
AVERAGE_CHARACTERISTIC = "3AFF"

async def main(address):
    async with BleakClient(address) as client:
        print("Connected")

        service = client.services.get_service('19B10000-E8F2-537E-4F6C-D104768A1214')
        text_char = service.get_characteristic(TEXT_CHARACTERISTIC)
        colour_char = service.get_characteristic(COLOUR_CHARACTERISTIC)
        font_char = service.get_characteristic(FONT_CHARACTERISTIC)
        status_char = service.get_characteristic(STATUS_CHARACTERISTIC)
        length_char = service.get_characteristic(LENGTH_CHARACTERISTIC)
        go_char = service.get_characteristic(GO_CHARACTERISTIC)
        reset_char = service.get_characteristic(RESET_CHARACTERISTIC)
        invert_char = service.get_characteristic(INVERT_CHARACTERISTIC)
        scroll_char = service.get_characteristic(AUTOSCROLL_CHARACTERISTIC)
        ribbon_char = service.get_characteristic(RIBBON_CHARACTERISTIC)
        avg_char = service.get_characteristic(AVERAGE_CHARACTERISTIC)

        rst = "R"
        while (rst.capitalize()!="Q"):
            await client.write_gatt_char(reset_char, b"\x01",response=True)
            advancedMode = False

            text = input("Press 'A' for advanced mode or \nEnter text to be displayed on the curtain: ")
            #text="Thanks for Listening!"
            if (text.capitalize()=="A"):
                advancedMode = True
                text = input("Enter text to be displayed on the curtain: ")
            await client.write_gatt_char(text_char, text.encode(),response=True)

            await asyncio.sleep(0.5)
            length = int.from_bytes(await client.read_gatt_char(length_char),'little')/100

            print("That text will take up "+str(length)+" meters")

            colourNum = -1
            while colourNum == -1:
                #colour="1"
                colour = input("Which colour map should the curtain use?\n[R]ed, [G]reen [B]lue, 1, 2, or 3 (various colours): ")
                
                if(colour.capitalize()=="R"):
                    colourNum = 0
                elif (colour.capitalize()=="G"):
                    colourNum = 1
                elif (colour.capitalize()=="B"):
                    colourNum = 2
                elif (colour=="1"):
                    colourNum = 3
                elif (colour=="2"):
                    colourNum = 4
                elif (colour=="3"):
                    colourNum = 5
                else:
                    print("Please enter 'R','G, 'B','1','2' or'3'")
                        
            await client.write_gatt_char(colour_char, colourNum.to_bytes(1,'big'),response=True)
            print("Fonts")
            print("0- Bold 8x8")
            print("1- Blade Runner 8x16")
            print("2- Ye Olde 8x16")
            print("3- 8x16")
            print("4- 8x19")
            print("5- 8x14")
            font=int(input("Choose a font 0-5: "))
            #font=3
            await client.write_gatt_char(font_char, font.to_bytes(1,'big'),response=True)

            # Autoscroll Default for demo
            #await client.write_gatt_char(scroll_char, b"\x01",response=True)

            if(advancedMode):
                inv = input("Invert the lights? [Y]/[N]")
                if (inv.capitalize()=="Y"):
                    await client.write_gatt_char(invert_char, b"\x01",response=True)

                scroll = input("Autoscroll the lights? [Y]/[N]")
                if (scroll.capitalize()=="Y"):
                    print("Scrolling")
                    await client.write_gatt_char(scroll_char, b"\x01",response=True)

                ribbon = input("Add a ribbon? [Y]/[N]")
                if (ribbon.capitalize()=="Y"):
                    await client.write_gatt_char(ribbon_char, b"\x01",response=True)
                
                average = input("Average the speed values? [Y]/[N]")
                if (average.capitalize()=="N"):
                    await client.write_gatt_char(ribbon_char, b"\x00",response=True)
                
            input("Setup!\nPress RETURN to begin")

            await client.write_gatt_char(go_char, b"\x01",response=True)

            print("Sent, please wait for GNSS connection")

            gps=0
            while(gps==0):
                gps = int.from_bytes(await client.read_gatt_char(status_char),'little')
            print("GPS Connected, please hold the curtain still for 10 seconds")

            while(gps==1):
                gps = int.from_bytes(await client.read_gatt_char(status_char),'little')
            print("Thank you, ready to proceed")

            rst = input("Press r to reset or q to quit")

            if(rst.capitalize()!="Q"):
                await client.write_gatt_char(reset_char, b"\x01",response=True)

asyncio.run(main(ADDRESS))