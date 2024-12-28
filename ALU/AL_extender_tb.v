module AL_extender_tb();
    // Testbench signals
    reg [3:0] A, B;
    wire [3:0] IA, IB;
    wire Cin;
    reg [2:0] Control;
    wire [3:0] Output;
    wire Cout;
    
    // Instantiate the module under test
    AL_extender uut (
        .A(A),
        .B(B),
        .IA(IA),
        .IB(IB),
        .Cin(Cin),
        .Control(Control),
        .Output(Output),
        .Cout(Cout)
    );
    
    // For checking results
    integer errors = 0;
    
    // Test stimulus
    initial begin
        // Initialize inputs
        A = 0;
        B = 0;
        Control = 0;
        
        // Wait for any initial settling
        #10;
        
        // Test case 1: Addition (000)
        $display("\nTesting Addition (000):");
        Control = 3'b000;
        
        // Test multiple values
        test_addition(4'h5, 4'h3);  // 5 + 3
        test_addition(4'hF, 4'h1);  // 15 + 1 (overflow case)
        test_addition(4'h0, 4'h0);  // 0 + 0
        
        // Test case 2: Subtraction (001)
        $display("\nTesting Subtraction (001):");
        Control = 3'b001;
        
        test_subtraction(4'h8, 4'h3);  // 8 - 3
        test_subtraction(4'h3, 4'h8);  // 3 - 8 (negative result)
        test_subtraction(4'h5, 4'h5);  // 5 - 5
        
        // Test case 3: Increment (010)
        $display("\nTesting Increment (010):");
        Control = 3'b010;
        
        test_increment(4'h5);    // 5 + 1
        test_increment(4'hF);    // 15 + 1 (overflow)
        test_increment(4'h0);    // 0 + 1
        
        // Test case 4: Transfer A (011)
        $display("\nTesting Transfer A (011):");
        Control = 3'b011;
        
        test_transfer(4'h5);
        test_transfer(4'hF);
        test_transfer(4'h0);
        
        // Test case 5: AND (100)
        $display("\nTesting AND (100):");
        Control = 3'b100;
        
        test_and(4'h5, 4'h3);
        test_and(4'hF, 4'h0);
        test_and(4'hA, 4'h5);
        
        // Test case 6: OR (101)
        $display("\nTesting OR (101):");
        Control = 3'b101;
        
        test_or(4'h5, 4'h3);
        test_or(4'hF, 4'h0);
        test_or(4'hA, 4'h5);
        
        // Test case 7: XOR (110)
        $display("\nTesting XOR (110):");
        Control = 3'b110;
        
        test_xor(4'h5, 4'h3);
        test_xor(4'hF, 4'h0);
        test_xor(4'hA, 4'h5);
        
        // Test case 8: NOT (111)
        $display("\nTesting NOT (111):");
        Control = 3'b111;
        
        test_not(4'h5);
        test_not(4'hF);
        test_not(4'h0);
        
        // Report final results
        $display("\nTest completed with %d errors", errors);
        $finish;
    end
    
    // Task for testing addition
    task test_addition;
        input [3:0] a, b;
        reg [4:0] expected;
        begin
            A = a;
            B = b;
            expected = a + b;
            #10;
            if (Output !== expected[3:0] || Cout !== expected[4]) begin
                $display("Error: %h + %h = %h (got Output=%h, Cout=%b)", 
                    a, b, expected, Output, Cout);
                errors = errors + 1;
            end else begin
                $display("Success: %h + %h = %h", a, b, Output);
            end
        end
    endtask
    
    // Task for testing subtraction
    task test_subtraction;
        input [3:0] a, b;
        reg [4:0] expected;
        begin
            A = a;
            B = b;
            expected = a - b;
            #10;
            if (Output !== expected[3:0]) begin
                $display("Error: %h - %h = %h (got %h)", 
                    a, b, expected[3:0], Output);
                errors = errors + 1;
            end else begin
                $display("Success: %h - %h = %h", a, b, Output);
            end
        end
    endtask
    
    // Task for testing increment
    task test_increment;
        input [3:0] a;
        reg [4:0] expected;
        begin
            A = a;
            expected = a + 1;
            #10;
            if (Output !== expected[3:0] || Cout !== expected[4]) begin
                $display("Error: %h + 1 = %h (got Output=%h, Cout=%b)", 
                    a, expected, Output, Cout);
                errors = errors + 1;
            end else begin
                $display("Success: %h + 1 = %h", a, Output);
            end
        end
    endtask
    
    // Task for testing transfer
    task test_transfer;
        input [3:0] a;
        begin
            A = a;
            #10;
            if (Output !== a) begin
                $display("Error: Transfer %h (got %h)", a, Output);
                errors = errors + 1;
            end else begin
                $display("Success: Transfer %h", a);
            end
        end
    endtask
    
    // Task for testing AND
    task test_and;
        input [3:0] a, b;
        reg [3:0] expected;
        begin
            A = a;
            B = b;
            expected = a & b;
            #10;
            if (Output !== expected) begin
                $display("Error: %h & %h = %h (got %h)", 
                    a, b, expected, Output);
                errors = errors + 1;
            end else begin
                $display("Success: %h & %h = %h", a, b, Output);
            end
        end
    endtask
    
    // Task for testing OR
    task test_or;
        input [3:0] a, b;
        reg [3:0] expected;
        begin
            A = a;
            B = b;
            expected = a | b;
            #10;
            if (Output !== expected) begin
                $display("Error: %h | %h = %h (got %h)", 
                    a, b, expected, Output);
                errors = errors + 1;
            end else begin
                $display("Success: %h | %h = %h", a, b, Output);
            end
        end
    endtask
    
    // Task for testing XOR
    task test_xor;
        input [3:0] a, b;
        reg [3:0] expected;
        begin
            A = a;
            B = b;
            expected = a ^ b;
            #10;
            if (Output !== expected) begin
                $display("Error: %h ^ %h = %h (got %h)", 
                    a, b, expected, Output);
                errors = errors + 1;
            end else begin
                $display("Success: %h ^ %h = %h", a, b, Output);
            end
        end
    endtask
    
    // Task for testing NOT
    task test_not;
        input [3:0] a;
        reg [3:0] expected;
        begin
            A = a;
            expected = ~a;
            #10;
            if (Output !== expected) begin
                $display("Error: ~%h = %h (got %h)", 
                    a, expected, Output);
                errors = errors + 1;
            end else begin
                $display("Success: ~%h = %h", a, Output);
            end
        end
    endtask
    
endmodule