import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.io.Writer;
import java.lang.ProcessBuilder.Redirect;
import java.util.Arrays;
import java.util.LinkedList;
import java.util.List;
import javafx.application.Application;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Orientation;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.SplitPane;
import javafx.scene.control.TextArea;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import javafx.stage.Stage;


public class MiniIDE extends Application 
{
	public static final int WIN_WIDTH = 1200;
	public static final int WIN_HEIGHT = 700;
	private TextArea screenl; 
	private Pane screenr; 
	private Button buttonHuff,buttonReg,buttonRegDfa,buttonStackParse, parserGen, LL1RecParse;
	private Button printButton, prettyButton, APIButton, javaButton, runJavaButton, javaDecode;
	private Button mipyDecode, byteCodeView, byteCodeRun, refParams, generators, staticBtn; 
	@Override
	public void start(Stage primaryStage) 
	{
		screenl = new TextArea(); 
		screenr = new Pane();
		screenr.setMinHeight(600);
		screenr.setMinWidth(600);

		screenl.setMinHeight(600);
		screenl.setPrefColumnCount(10);
		screenl.setMinWidth(600);

		// create the buttons
		buttonHuff = new Button("Run");
		buttonReg = new Button("RegEx");
		buttonRegDfa = new Button("RegEx+DFA");
		buttonStackParse = new Button("LL(1) Stack Parse");
		parserGen = new Button("Parser Gen");
		LL1RecParse = new Button("LL(1) Rec Parse");   
		printButton = new Button("Print"); 
		prettyButton = new Button("Pretty"); 
		APIButton = new Button("API"); 
		javaButton = new Button("Java"); 
		runJavaButton = new Button("Run Java");
		javaDecode = new Button("Java Decode");
		mipyDecode = new Button("Mipy Decode");
		byteCodeView = new Button("ByteCode View");
		byteCodeRun = new Button("ByteCode Run");
		//refParams, generators
    		refParams = new Button("Mipy RefParams");
    		generators = new Button("Mipy Generators");
    		staticBtn =  new Button("Mipy Static");

		// attach a handler to process button clicks    
		buttonHuff.setOnAction(new HuffButtonHandler());
		buttonReg.setOnAction(new RegButtonHandler());      
		buttonRegDfa.setOnAction(new dfaRegButtonHandler());
		buttonStackParse.setOnAction(new stackParseHandler());
		parserGen.setOnAction(new parserGenHandler());
		LL1RecParse.setOnAction(new recParseHandler());
		printButton.setOnAction(new PrintButtonHandler());
		prettyButton.setOnAction(new PrettyButtonHandler());
		APIButton.setOnAction(new APIButtonHandler());
		javaButton.setOnAction(new JavaButtonHandler());
		runJavaButton.setOnAction(new runJavaButtonHandler());
		javaDecode.setOnAction(new DecodeJavaButtonHandler());
		mipyDecode.setOnAction(new DecodeMipyButtonHandler());
		byteCodeView.setOnAction(new byteCodeViewButtonHandler());
		byteCodeRun.setOnAction(new byteCodeRunButtonHandler());
		refParams.setOnAction(new RefParamButtonHandler());
    		generators.setOnAction(new GeneratorButtonHandler());
    		staticBtn.setOnAction(new StaticButtonHandler());


		SplitPane splitPane = new SplitPane(screenl, screenr);
		splitPane.setMinSize(WIN_WIDTH, WIN_HEIGHT-100);

		GridPane buttonPane= new GridPane();
		buttonPane.add(buttonHuff, 0, 0);
		buttonPane.add(buttonReg,1,0);
		buttonPane.add(buttonRegDfa,2,0);
		buttonPane.add(buttonStackParse,3,0);
		buttonPane.add(parserGen, 4, 0);
		buttonPane.add(LL1RecParse, 5, 0);
		buttonPane.add(printButton,6,0);
		buttonPane.add(prettyButton,7,0);
		buttonPane.add(APIButton,8,0);
		buttonPane.add(javaButton,9,0);
		buttonPane.add(runJavaButton,10,0);
		buttonPane.add(javaDecode,11,0);
		buttonPane.add(mipyDecode,12,0);
		buttonPane.add(byteCodeView,13,0);
		buttonPane.add(byteCodeRun,14,0);
		buttonPane.add(refParams,15,0);		
		buttonPane.add(generators,16,0);
    		buttonPane.add(staticBtn,17,0);

		SplitPane mainPane = new SplitPane(buttonPane, splitPane);
		mainPane.setOrientation(Orientation.VERTICAL);
		// set up the scene
		Scene scene = new Scene(mainPane); 

		primaryStage.setTitle("MiniIDE");
		primaryStage.setScene(scene);
		primaryStage.show();
	}


	public void executeProcess(String program, String args, boolean stdinPipe, String stdoutFile, boolean replace){
		LinkedList<String> command = new LinkedList<>();

		//python 3 or file path
		command.add(program);

		//add arguments if there
		System.out.println("Program is: " + program);
		System.out.println("Args are: " + args);
		if(args!=null) {
			command.addAll(new LinkedList<>(Arrays.asList(args.split("\\s+"))));
		}

		//make process builder with arguments if there
		ProcessBuilder processbuilder = new ProcessBuilder(command);
		//also redirect input stream
		processbuilder.redirectErrorStream(true);
		//if we are redirecting output to file, prep the file
		if(stdoutFile!= null) {
			writeToFile(stdoutFile, processbuilder);
		}
		Process process;
		try {
			//start
			process = processbuilder.start();
			//cat if needed
			if(stdinPipe) {
				writeFromLeft(process, replace);
			}
			//if showing to the right
			if(stdoutFile==null) {
				writeToRight(process);
			}
			process.waitFor();			
		}
		catch (IOException | InterruptedException e) {
			e.printStackTrace();
		}
	}



	//writes to the output stream of the process
	public void writeFromLeft(Process process, boolean replace) {		
		OutputStream oStream = process.getOutputStream();
		Writer oStreamWriter = new OutputStreamWriter(oStream);
		String code;		
		if(replace){
			String[] leftpanel = screenl.getText().trim().replaceAll("\\s+", " ").split("\\r?\\n");
			code = String.join(" ", leftpanel);
		}
		else {
			code = screenl.getText().trim();
		}		
		code = code + "\n";

		try {
			//System.out.println("code is: " + String.join(" ", code));
			oStreamWriter.write(code);			
			oStreamWriter.close();
			oStream.close();

		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void writeToRight(Process process) {
		InputStream inputStream = process.getInputStream();
		BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(inputStream), 1);
		TextFlow rightText =new TextFlow();
		String line;
		try {
			while ((line = bufferedReader.readLine()) != null) {
				System.out.println(line);
				rightText.getChildren().add(new Text(line));
				rightText.getChildren().add(new Text("\n"));	
			}
			screenr.getChildren().add(rightText);	
			inputStream.close();
			bufferedReader.close();	
		} catch (IOException e) {
			e.printStackTrace();
		}
	}


	public void writeToFile(String filename, ProcessBuilder builder) {
		File nFile = new File(filename);
		if(!nFile.exists()) {
			try {
				nFile.createNewFile();
				builder.redirectOutput(Redirect.to(nFile));
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}


	private class HuffButtonHandler implements EventHandler<ActionEvent>
	{        
		@Override 
		public void handle(ActionEvent e) 
		{
			screenr.getChildren().clear();
			String filePath = "../../proj1/HuffmanTree/main.exe";
			String textLeftPanel= screenl.getText();
			executeProcess(filePath,textLeftPanel,false,null, true);      
		} 
	}


	// Handler for processing the button clicks 
	private class RegButtonHandler implements EventHandler<ActionEvent>
	{        
		@Override 
		public void handle(ActionEvent e) 
		{
			screenr.getChildren().clear();
			String filePath = "../../proj4/re_test.py";
			String arguments = filePath+ " " + screenl.getText();
			executeProcess("python3",arguments,false, null, true);			
		} 
	}

	private class dfaRegButtonHandler implements EventHandler<ActionEvent>
	{        
		@Override 
		public void handle(ActionEvent e) 
		{
			screenr.getChildren().clear();
			String filePath = "../../proj4/re_dfa_test.py";
			String arguments = filePath+ " " + screenl.getText();
			executeProcess("python3",arguments,false, null, true);
		} 
	}


	private class stackParseHandler implements EventHandler<ActionEvent>
	{        
		@Override 
		public void handle(ActionEvent e)
		{
			screenr.getChildren().clear();
			String filePath = "../../proj4/parse_stack_test.py";
			executeProcess("python3", filePath, true, null, true);
		} 
	}

	private class parserGenHandler implements EventHandler<ActionEvent>
	{

		@Override
		public void handle(ActionEvent arg0) {
			screenr.getChildren().clear();
			String filePath = "../../proj4/parser_gen.py";
			String grammarFile = "logo_grammar.txt";
			String arguments= filePath + " " + grammarFile;
			executeProcess("python3", arguments, false, "../../proj4/logo_parser.py", true);
		}
	}


	private class recParseHandler implements EventHandler<ActionEvent>
	{

		public void handle(ActionEvent e) {
			screenr.getChildren().clear();
			String filePath = "../../proj4/logo_parser.py";
			executeProcess("python3", filePath, true, null, true);	
		}
	}



	//cat fibonacci.mipy | Debug/calc java

	//	printButton.setOnAction(new PrintButtonHandler());
	private class PrintButtonHandler implements EventHandler<ActionEvent>{

		@Override
		public void handle(ActionEvent event) {
			screenr.getChildren().clear();
			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"print",true,null, false); 			
		}

	}


	//	prettyButton.setOnAction(new PrettyButtonHandler());

	private class PrettyButtonHandler implements EventHandler<ActionEvent>{

		@Override
		public void handle(ActionEvent event) {
			screenr.getChildren().clear();
			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"pretty",true,null, false); 			
		}

	}


	//	APIButton.setOnAction(new APIButtonHandler());


	private class APIButtonHandler implements EventHandler<ActionEvent>{

		@Override
		public void handle(ActionEvent event) {
			screenr.getChildren().clear();
			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"api",true,null, false); 			
		}
	}


	//	javaButton.setOnAction(new JavaButtonHandler());

	private class JavaButtonHandler implements EventHandler<ActionEvent>{

		@Override
		public void handle(ActionEvent event) {
			screenr.getChildren().clear();
			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"java",true,null, false); 			
		}

	}


	//	runJavaButton.setOnAction(new runJavaButtonHandler());


	private class runJavaButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"java",true,"Program.java", false);
			executeProcess("javac", "Program.java", false, null, false);
			executeProcess("java", "Program", false, null, false); 
		}

	}

	private class DecodeJavaButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();

			try{
				PrintWriter writer = new PrintWriter("Program.java", "UTF-8");
				writer.println(screenl.getText());
				writer.close();
			}
			catch(IOException i){
				i.printStackTrace();
			}    		   

			String filePath = "../../proj7/Decoder/Debug/Decoder";    		   
			executeProcess("javac", "Program.java", false, null, false);
			executeProcess(filePath, "", false, null, false); 
		}

	}

	private class DecodeMipyButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	

			screenr.getChildren().clear();

			String filePath = "../../proj6/MiniPython/Debug/calc";
			executeProcess(filePath,"java",true,"Program.java", false);
			executeProcess("javac", "Program.java", false, null, false);

			String filePath2 = "../../proj7/Decoder/Debug/Decoder";
			executeProcess(filePath2, "", false, null, false); 
		}


	}
	
	
	private class byteCodeViewButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
    			String filePath = "../../proj8/MiniPythonJVM/Debug/calc";
      			executeProcess(filePath,"",true,"Program.class", false);
      			executeProcess("javap", "-v Program.class", false, null, false);
		}


	}
	
	
	private class byteCodeRunButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
      			String filePath = "../../proj8/MiniPythonJVM/Debug/calc";
      			executeProcess(filePath,"",true,"Program.class", false);
      			executeProcess("java", "Program", false, null, false);
		}


	}

	private class RefParamButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
      			String filePath = "../../proj10/MiniPythonJVM10/Debug/calc";
      			executeProcess(filePath,"",true, null, false);
      			executeProcess("java", "-Xverify:none Program", false, null, false);
		}


	}

	private class GeneratorButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
      			String filePath = "../../proj10/MiniPythonJVM10/Debug/calc";
      			executeProcess(filePath,"",true, null , false);
      			executeProcess("java", "-Xverify:none Program", false, null, false);
		}
	}
 
 	private class StaticButtonHandler implements EventHandler<ActionEvent>{

		public void handle(ActionEvent event) {	
			screenr.getChildren().clear();
      			String filePath = "../../proj11/MiniPythonJVM11/Debug/calc";
      			executeProcess(filePath,"",true, null , false);
      			executeProcess("java", "-Xverify:none Program", false, null, false);
		}
	}
	
	public static void main(String[] args) 
	{
		launch(args);
	}
}
