სახელი

	fsh - არის shell ის იმპლემენტაცია, რისი დახმარებითაც შეიძლება სხვადასხვა ბრძანებების განხორციელება.

SYNOPSiS

	./shell 

აღწერა

	fsh-ს საშუალებით შეიძლება სხვადასხვა ბრძანებების შესრულება. ის ასრულებს როგორც built in ასევე არა built in ბრძანებებსაც. მისი built in ფუნქციებია cd,pwd,kill da ა.შ. redirect ების საშუალებით შეგვიძლია ვცვალოთ პროგრამის input და output ფაილები.  შელის დახმარებით შეგვიძლია გავუშვათ სხვადასხცა პროცესი ან შევცვალოთ პროცესის პრიორიტეტბი და გავიგზავნოთ სხვადსხვა სიგნალები.

მაგალითები

	kill -signal_id proces_id გაუგზავნის სიგნალს პროცესს რომლის id იც არის process_id.

	ulimit -a ჩამოწერს მინდინარე პროცესისადმი მინიჭებულ ლიმიტებს

exit status 
	პროგრამის წარმატებულად დასრულების შემთხვევაში ბრუნდება 0 იანი

პროგრამა არ რეაგირებს crtl + c და crtl +z ზე ამიტომ პროგრამის გასათიშად საჭიროა აკრიბოთ exit

ფაილები

shell.c და shell.h  მთავარი გამშვები shell ის ჰედერ და სი ფაილები.

cd_m.c და cd_m.h ფაილი სადაც წერია დირექტორიის შესაცვლელად საჭირო კოდი.

export_m.c და export_m.h ფაილები სადაც წერა ინფუთის და აუთფუთის შესაცვლელად საჭირო კოდი.
 ...


დამხმარე ფაილები

	procps.h sig.h sig.c რომელიც გამოიყენება kill ბრძანების გამოძახების ყველა სინოფსისის გასათვალისწინებლად. მაგალითად შეგვიძლია გამოვიძახოთ როგორც 
	kill -SIGSTOP 3350
	kill -s SIGSTOP 3350
	kill -STOP 3350
	kill -19 3350  

	რაც ამოიწვევს იმ პროცესის დაპაუზებას რომლის პროცესის ნომერია 3350.

ისტორია 

	შექმნილია თორნიკე აბულაძის მიხეილ მაღრიანისა და ლაშა გურეშიძის მიერ 2015 წლის მარტში.
