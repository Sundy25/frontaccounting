<?php
class hooks_pl_PL {
	function  _price_segment($amount) {

	$jedn = array(
		'jeden','dwa','trzy','cztery','pi��',
		'sze��','siedem','osiem','dziewi��','dziesi��',
		'jedena�cie','dwana�cie','trzyna�cie', 'czterna�cie','pi�tna�cie',
		'szesna�cie', 'siedemna�cie', 'osiemna�cie','dziewi�tna�cie');

	$dzies = array(
		'dwadzie�cia','trzydzie�ci','czterdzie�ci','pi��dziesi�t','sze��dziesi�t',
		'siedemdziesi�t','osiemdziesi�t','dziewi��dziesi�t');

	$setki = array('sto','dwie�cie','trzysta','czterysta','pi��set',
		'sze��set','siedemset','osiemset','dziewi��set');

		$set = floor($amount/100);
		$dzi = floor(($amount - $set*100)/10);
		$jed = $amount%10;

		if ($dzi == 1) {
			$dzi = 0;
			$jed += 10;
		}
		$str = '';

		if ($set)
			$str = ' '.$setki[$set-1];
		if ($dzi)
			$str .= ' '.$dzies[$dzi-2];
		if ($jed)
			$str .= ' '.$jedn[$jed-1];

		return $str;
	}
	
	function price_in_words($amount, $doc_type=null)
	{
		$amount += ($amount < 0 ? -.000001 : .000001);

		$mrd =  floor($amount/1.0e9);
		$amount -= $mrd*1.0e9;
		$mil =  floor($amount/1.0e6);
		$amount -= $mil*1.0e6;
		$tys =  floor($amount/ 1.0e3);
		$amount -= $tys*1.0e3;
		$jed = (int)($amount);
		$grosze = (int)(($amount- $jed)*100);

		$buf = '';

		if ($mrd)
			$buf .= $this->_price_segment( $mrd ). " miliard".
				($mrd==1 ? "" : (($mrd%10)<5 && ($mrd>20 || $mrd<10) ? "y" : "�w"));

		if ($mil)
			$buf .= $this->_price_segment( $mil ). " milion".
				($mil==1 ? "" : (($mil%10)<5 && (($mil%20)>1 && ($mil>20 || $mil<10)) ? "y" :"�w"));
		if ($tys)
			$buf .= $this->_price_segment( $tys ). " tysi".
				($tys==1 ? "�c" : (($tys%10)>1 && $tys%10<5 && 
					(($tys%20)>1 && ($tys>20 || $tys<10)) ? "�ce" :"�cy"));

		if ($jed)
			$buf .= $this->_price_segment( $jed );

		if ($buf == '')
			$buf= 'zero';

		if ($tys || $mil || $mrd || ($jed > 4 || !$jed))
			$buf .= ' z�otych';
		else
			if ( $jed == 1)
				$buf .= ' z�oty';
			else
				$buf .= ' z�ote';

//			$buf .= " $grosze/100 gr";

		if ($grosze)
			$buf .= ' '.$this->_price_segment($grosze);
		else
			$buf .= ' zero';

		$grosze %= 10;
		if (!$grosze || $grosze>4)
			$buf .= ' groszy';
		else $buf .= $grosze == 1 ? ' grosz' : ' grosze';

		return "S�ownie: ".$buf;
	}



}
?>