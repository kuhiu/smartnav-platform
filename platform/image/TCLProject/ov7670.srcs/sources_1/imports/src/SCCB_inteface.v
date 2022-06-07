`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 07/03/2021 04:51:56 PM
// Design Name: 
// Module Name: SCCB_inteface
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////

// modelo : https://github.com/westonb/OV7670-Verilog/blob/master/src/SCCB_interface.v

module SCCB_inteface
#(
    parameter CLK_FREQ  = 25000000,
    parameter SCCB_FREQ = 100000
)
(
    input wire clk,             
    input wire start,           // Entrada valida, comenzar a enviar
    input wire [7:0] address,   // Direccion del esclavo
    input wire [7:0] data,      // Datos
    output reg ready,           // 0: Enviando, 1: Listo para enviar
    output reg SIOC,            // Clk del protocolo
    output reg SIOD             // Datos del protocolo
    );
    
    
    localparam CAMERA_ADDR          = 8'h42;
    localparam STATE_IDLE           = 4'd0;
    localparam STATE_START_SIGNAL   = 4'd1;
    localparam STATE_LOAD_BYTE      = 4'd2;
    localparam STATE_TX_BYTE_1      = 4'd3;
    localparam STATE_TX_BYTE_2      = 4'd4;
    localparam STATE_TX_BYTE_3      = 4'd5;
    localparam STATE_TX_BYTE_4      = 4'd6;
    localparam STATE_END_SIGNAL_1   = 4'd7;
    localparam STATE_END_SIGNAL_2   = 4'd8;
    localparam STATE_END_SIGNAL_3   = 4'd9;
    localparam STATE_END_SIGNAL_4   = 4'd10;
    localparam STATE_DONE           = 4'd11;
    localparam STATE_TIMER          = 4'd12;
    
    reg [3:0] state = STATE_IDLE;
    reg [3:0] next_state;
    reg [3:0] return_state;
    
    reg [8-1:0] r_addr;
    reg [8-1:0] r_data;
    reg [8-1:0] byte_counter;   // SCCB necesita enviar 3 bytes, device address,
                                // register address, write data
    reg [4-1:0] bit_index;      // Va a servir para ir contando 
                                // cuantos bits se enviaron en cada byte
    reg [31-1:0] timer;         // Se necesita un contador para cumplir con el protocolo 
    reg [8-1 :0] tx_byte;
    
    always @(posedge clk) begin
        if (start)
            state <= next_state;
    end
    
    
    always @(posedge clk) begin
    
        case (state) 
        
            STATE_IDLE: begin
                bit_index       <= 3'b0;    // Reset bits enviados
                byte_counter    <= 8'b0;    // Reset bytes enviados
                if (start) begin
                    next_state  <= STATE_START_SIGNAL;
                    r_addr      <= address;     // Latch de entrada
                    r_data      <= data;        // Latch de datos
                    ready       <= 1'b0;
                end
                else 
                    ready       <= 1'b1;    
            end
            
            STATE_START_SIGNAL: begin       // Comienza la comunicacion con SIOD low y espera 
                SIOC            <= 1'b0;
                SIOD            <= 1'b1;
                next_state      <= STATE_TIMER;
                return_state    <= STATE_LOAD_BYTE;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
            end
            
            STATE_LOAD_BYTE : begin             // Carga el byte a enviar, si ya envio los 3 salta a STATE_END_SIGNAL_1
                if (byte_counter == 3)
                    next_state <= STATE_END_SIGNAL_1;
                else
                    next_state <= STATE_TX_BYTE_1;
                    
                byte_counter    <= byte_counter + 1;
                bit_index       <= 3'b0;
                
                case(byte_counter)
                    0: tx_byte <= CAMERA_ADDR;
                    1: tx_byte <= r_addr;
                    2: tx_byte <= r_data;
                    default: tx_byte <= r_data;
                endcase
            end
            
            STATE_TX_BYTE_1: begin              // Baja SIOC y delay 
                SIOC            <= 1'b1;
                next_state      <= STATE_TIMER;
                return_state    <= STATE_TX_BYTE_2;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
            end
            
            STATE_TX_BYTE_2: begin              // Asigno la salida 
                next_state      <= STATE_TIMER;
                return_state    <= STATE_TX_BYTE_3;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
                if (bit_index == 4'd8)
                    SIOD <= 1'b0;
                else 
                    SIOD <= ~tx_byte[7];
            end
            
            STATE_TX_BYTE_3: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_TX_BYTE_4;
                timer           <= (CLK_FREQ/(2*SCCB_FREQ));
                SIOC            <= 1'b0;
            end
            
            STATE_TX_BYTE_4: begin
                if(bit_index)
                    next_state      <= STATE_LOAD_BYTE;
                
                tx_byte         <= tx_byte<<1;
                bit_index       <= bit_index + 1;
            end
                
            STATE_END_SIGNAL_1: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_END_SIGNAL_2;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
                SIOC            <= 1'b1;
            end
            
            STATE_END_SIGNAL_2: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_END_SIGNAL_3;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
                SIOD            <= 1'b1;
            end
            
            STATE_END_SIGNAL_3: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_END_SIGNAL_4;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
                SIOC            <= 1'b0;
            end
            
            STATE_END_SIGNAL_4: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_DONE;
                timer           <= (CLK_FREQ/(4*SCCB_FREQ));
                SIOD            <= 1'b0;            
            end
            
            STATE_DONE: begin
                next_state      <= STATE_TIMER;
                return_state    <= STATE_IDLE;
                timer           <= (CLK_FREQ/(2*SCCB_FREQ));
                byte_counter    <= 8'b0;    
            end
            
            STATE_TIMER: begin
                if (timer == 0) begin 
                    next_state <= return_state;
                    timer <= 0;
                end else begin
                    next_state <= STATE_TIMER;
                    timer <= timer - 1; 
                end
            end
            
        endcase
    end
    
    
    
endmodule
