public class OrdinateurPortable extends Materiel implements Empruntable{
    private String marque;
    private Os systeme;
    private boolean estDisponible;
    public OrdinateurPortable(boolean enPanne, String marque, Os systeme){
        super(enPanne);
        this.marque=marque;
        this.systeme=systeme;
    }
    public boolean estDisponible(){
        return this.estDisponible;
    }
    public void emprunter(){
        this.estDisponible=false;

    }
    public void rendre(){
        this.estDisponible=true;
    }
    public String getMarque(){
        return this.marque;
    }
    public Os getSysteme(){
        return this.systeme;
    }
}
